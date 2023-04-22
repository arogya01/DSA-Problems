// node --trace-events enable

let counter = 0;

setInterval(() => {
  for (index = 0; index < 1e9; index++);
  if (counter++ >= 10) process.exit();
  console.log("test");
});
