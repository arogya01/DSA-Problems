#!/usr/bin/env node

const fs = require('fs');
const path = require('path');
const os = require('os');
const crypto = require('crypto');
const { execSync } = require('child_process');

// Generate a random device ID
function generateDeviceId() {
    return crypto.randomBytes(16).toString('hex');
}

// Function to get Cursor config directory path based on OS
function getCursorConfigPath() {
    const platform = os.platform();
    let configPath;

    if (platform === 'win32') {
        configPath = path.join(os.homedir(), 'AppData', 'Roaming', 'Cursor', 'Session Storage');
    } else if (platform === 'darwin') {
        configPath = path.join(os.homedir(), 'Library', 'Application Support', 'Cursor', 'User', 'globalStorage');
    } else if (platform === 'linux') {
        configPath = path.join(os.homedir(), '.config', 'Cursor', 'Session Storage');
    } else {
        console.error('Unsupported operating system');
        process.exit(1);
    }

    return configPath;
}

// Function to reset Cursor device ID
function resetCursorLimit() {
    try {
        console.log('Starting Cursor limit reset...');
        
        // Get config path based on OS
        const configPath = getCursorConfigPath();
        console.log(`Config path: ${configPath}`);
        
        // Check if Cursor is installed
        if (!fs.existsSync(configPath)) {
            console.error('Cursor configuration not found. Is Cursor installed?');
            process.exit(1);
        }
        
        const platform = os.platform();
        
        if (platform === 'darwin') {
            // For macOS, handle the specific storage.json file
            const storageFile = path.join(configPath, 'storage.json');
            
            if (!fs.existsSync(storageFile)) {
                console.error(`Storage file not found at: ${storageFile}`);
                process.exit(1);
            }
            
            console.log(`Processing file: ${storageFile}`);
            
            // Create backup
            const backupPath = `${storageFile}.backup`;
            fs.copyFileSync(storageFile, backupPath);
            console.log(`Backup created at: ${backupPath}`);
            
            // Read current config
            try {
                const content = fs.readFileSync(storageFile, 'utf8');
                const config = JSON.parse(content);
                
                // Reset device ID if exists (search for any device_id fields in the config)
                let modified = false;
                
                const processObject = (obj, path = '') => {
                    if (!obj || typeof obj !== 'object') return;
                    
                    for (const key in obj) {
                        if (key === 'device_id' || key === 'installation_id' || key === 'machine_id') {
                            const oldValue = obj[key];
                            obj[key] = generateDeviceId();
                            console.log(`Changed ${path}${key} from ${oldValue} to ${obj[key]}`);
                            modified = true;
                        } else if (typeof obj[key] === 'object') {
                            processObject(obj[key], `${path}${key}.`);
                        }
                    }
                };
                
                processObject(config);
                
                if (modified) {
                    // Save modified config back to file
                    fs.writeFileSync(storageFile, JSON.stringify(config, null, 2));
                    console.log('Configuration successfully updated.');
                } else {
                    console.log('No device identifiers found to reset.');
                }
            } catch (error) {
                console.error('Error parsing or modifying configuration:', error);
                console.log('Restoring backup...');
                fs.copyFileSync(backupPath, storageFile);
                console.log('Backup restored.');
            }
        } else {
            // For other platforms, use the existing logic
            const files = fs.readdirSync(configPath);
            const localStateFiles = files.filter(file => file.includes('local_state'));
            
            if (localStateFiles.length === 0) {
                console.error('No local_state files found in the configuration directory.');
                process.exit(1);
            }
            
            for (const file of localStateFiles) {
                const filePath = path.join(configPath, file);
                console.log(`Processing file: ${filePath}`);
                
                // Create backup
                const backupPath = `${filePath}.backup`;
                fs.copyFileSync(filePath, backupPath);
                console.log(`Backup created at: ${backupPath}`);
                
                // Read current config
                let content = fs.readFileSync(filePath, 'utf8');
                
                try {
                    // The file content might be in a special format with a key and JSON data
                    // Try to extract the JSON part
                    if (content.includes('{"local_state":')) {
                        const jsonStart = content.indexOf('{"local_state":');
                        content = content.substring(jsonStart);
                    }
                    
                    const config = JSON.parse(content);
                    
                    // Reset device ID if exists
                    if (config.local_state && config.local_state.device_id) {
                        const oldDeviceId = config.local_state.device_id;
                        config.local_state.device_id = generateDeviceId();
                        console.log(`Device ID changed from ${oldDeviceId} to ${config.local_state.device_id}`);
                    }
                    
                    // Reset any other tracking identifiers that might exist
                    if (config.local_state) {
                        if (config.local_state.installation_id) {
                            config.local_state.installation_id = generateDeviceId();
                        }
                        if (config.local_state.machine_id) {
                            config.local_state.machine_id = generateDeviceId();
                        }
                    }
                    
                    // Save modified config back to file
                    fs.writeFileSync(filePath, JSON.stringify(config, null, 2));
                    console.log('Configuration successfully updated.');
                } catch (error) {
                    console.error('Error parsing or modifying configuration:', error);
                    console.log('Restoring backup...');
                    fs.copyFileSync(backupPath, filePath);
                    console.log('Backup restored.');
                }
            }
        }
        
        console.log('Process completed. Please restart Cursor for changes to take effect.');
        
        // Kill any running Cursor instances
        try {
            if (os.platform() === 'win32') {
                execSync('taskkill /F /IM "Cursor.exe" /T', { stdio: 'ignore' });
            } else {
                execSync('pkill -f "Cursor"', { stdio: 'ignore' });
            }
            console.log('Cursor application has been closed.');
        } catch (error) {
            console.log('No running Cursor instances found or unable to close Cursor.');
        }
        
    } catch (error) {
        console.error('An error occurred:', error);
    }
}

// Run the function
resetCursorLimit();