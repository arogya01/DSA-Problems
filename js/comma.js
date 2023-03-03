const refine = (data) => ({ id: data.id === 1, message: "Hello World" });

console.log(refine({ id: 2 }));
