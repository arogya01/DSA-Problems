const inventory = [
    { name: "asparagus", type: "vegetables" },
    { name: "bananas", type: "fruit" },
    { name: "goat", type: "meat" },
    { name: "cherries", type: "fruit" },
    { name: "fish", type: "meat" },
  ];

  
  const result = inventory.group(({ type }) => type);
console.log(result.vegetables);
// [{ name: "asparagus", type: "vegetables" }]
