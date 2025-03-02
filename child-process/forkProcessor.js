process.on('message', (message) => {
    console.log('message from parent', message); 
}); 

let counter = 0; 

for(let i = 0; i < 100; i++){
    process.send(`${i}`);
}

