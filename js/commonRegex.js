
const commonRegExp = {
    replaceSpecialChars:  /[^\w\s]/gi
};
// Case 1: requestData is undefined
let requestData;
let supplierAddress = `${requestData?.clinicDetails?.facilityAddress}`.replace(commonRegExp.replaceSpecialChars, "");
console.log(supplierAddress); // Outputs: "undefined"

// Case 2: clinicDetails is undefined
requestData = {};
supplierAddress = `${requestData?.clinicDetails?.facilityAddress}`.replace(commonRegExp.replaceSpecialChars, "");
console.log(supplierAddress); // Outputs: "undefined"

// Case 3: facilityAddress is undefined
requestData = { clinicDetails: {} };
supplierAddress = `${""}`.replace(commonRegExp.replaceSpecialChars, "");
console.log(supplierAddress); // Outputs: "undefined"