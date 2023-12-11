// Specializations of a doctor
const doctorSpecialization = ['cardiologist', 'dentist', 'dermatologist'];

// Function to check for excluded specializations
const checkForExcludedSpecialization = (doctorSpecialization, excludedSpecializations) => {
  return !excludedSpecializations.some(specialization => doctorSpecialization.includes(specialization));
};

// Example modal object
const modal = {
  additionalChecks: {
    excludedSpecializations: ['dentist']
  }
};

// The getAdditionalChecks function
const getAdditionalChecks = (modal) => {
  if (typeof modal === 'object' && Object.hasOwn(modal, 'additionalChecks')) {
    if (modal?.additionalChecks?.excludedSpecializations) {
      return checkForExcludedSpecialization(
        doctorSpecialization,
        modal?.additionalChecks?.excludedSpecializations,
      );
    }
  }
  return true;
};

// Running the check
const result = getAdditionalChecks(modal);
console.log(result); // This will log 'false' because 'dentist' is in the excluded list
