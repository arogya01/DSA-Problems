import {exec, execFile} from "child_process"; 
import path from "path"; 
import { fileURLToPath } from "url";
import {dirname} from "path"; 
import { fork } from "child_process";

// exec("ls -lh", (err, stdout, stderr) => {
//     if (err) {
//         console.error(`Error executing command: ${err}`);
//         return;
//     }

//     if(stderr) {
//         console.error(`Error executing command: ${stderr}`);
//         return;
//     }

//     console.log(stdout);
// });

//execFile 

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

const filesPath = path.resolve(__dirname, "execFileProcessor.js");

// console.log('filesPath', filesPath);
// execFile('node', [filesPath], (err, stdout, stderr) => {
//     if (err) {
//         console.error(`Error executing command: ${err}`);
//         return;
//     }

//     if (stderr) {
//         console.error(`Command stderr: ${stderr}`);
//         return;
//     }

//     console.log('Command output:', stdout);
// });


const forkProcessorPath = path.resolve(__dirname, "forkProcessor.js");
const forkedChild = fork(forkProcessorPath); 
forkedChild.on('message', (message)=> {
    console.log('Message from forked child:', message);
})

forkedChild.send('Hello from parent');