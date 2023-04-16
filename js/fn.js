const getFormattedGender = (gender) => {
  let genderValue = "";

  if (typeof gender === "object" && gender.value) {
    genderValue = gender.value.toLowerCase();
  } else if (typeof gender === "string") {
    genderValue = gender.toLowerCase();
  }

  return genderValue === "female" ? "F" : "M";
};

console.log(getFormattedGender("Female"));

console.log(
  getFormattedGender({
    value: "Female",
  })
);
console.log(
  getFormattedGender({
    value: "Male",
  })
);
console.log(
  getFormattedGender({
    value: "male",
  })
);
