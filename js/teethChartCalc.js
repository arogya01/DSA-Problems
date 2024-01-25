const teethChart = {
  chartId: 1,
  visibilityFixed: ["primary", "q1", "q2", "q3", "q4"],
  primary: {
    label: "Primary Teeth",
    isActive: true,
  },
  q1: {
    label: "UL",
    value: [
      "1",
      "2",
      "3",
      "4",
      "5",
      "6",
      "7",
      "8",
      "33",
      "34",
      "35",
      "36",
      "37",
    ],
  },
  q2: {
    label: "UR",
    value: [
      "9",
      "10",
      "11",
      "12",
      "13",
      "14",
      "15",
      "16",
      "38",
      "39",
      "40",
      "41",
      "42",
    ],
  },
  q3: {
    label: "BL",
    value: [
      "17",
      "18",
      "19",
      "20",
      "21",
      "22",
      "23",
      "24",
      "43",
      "44",
      "45",
      "46",
      "47",
    ],
  },
  q4: {
    label: "BR",
    value: [
      "25",
      "26",
      "27",
      "28",
      "29",
      "30",
      "31",
      "32",
      "48",
      "49",
      "50",
      "51",
      "52",
    ],
  },
  teethIds: {
    1: {
      label: "1",
      value: "1",
    },
    2: {
      label: "2",
      value: "2",
    },
    3: {
      label: "3",
      value: "3",
    },
    4: {
      label: "4",
      value: "4",
    },
    5: {
      label: "5",
      value: "5",
    },
    6: {
      label: "6",
      value: "6",
    },
    7: {
      label: "7",
      value: "7",
    },
    8: {
      label: "8",
      value: "8",
    },
    9: {
      label: "9",
      value: "9",
    },
    10: {
      label: "10",
      value: "10",
    },
    11: {
      label: "11",
      value: "11",
    },
    12: {
      label: "12",
      value: "12",
    },
    13: {
      label: "13",
      value: "13",
    },
    14: {
      label: "14",
      value: "14",
    },
    15: {
      label: "15",
      value: "15",
    },
    16: {
      label: "16",
      value: "16",
    },
    17: {
      label: "17",
      value: "17",
    },
    18: {
      label: "18",
      value: "18",
    },
    19: {
      label: "19",
      value: "19",
    },
    20: {
      label: "20",
      value: "20",
    },
    21: {
      label: "21",
      value: "21",
    },
    22: {
      label: "22",
      value: "22",
    },
    23: {
      label: "23",
      value: "23",
    },
    24: {
      label: "24",
      value: "24",
    },
    25: {
      label: "25",
      value: "25",
    },
    26: {
      label: "26",
      value: "26",
    },
    27: {
      label: "27",
      value: "27",
    },
    28: {
      label: "28",
      value: "28",
    },
    29: {
      label: "29",
      value: "29",
    },
    30: {
      label: "30",
      value: "30",
    },
    31: {
      label: "31",
      value: "31",
    },
    32: {
      label: "32",
      value: "32",
    },
    33: {
      label: "A",
      value: "33",
    },
    34: {
      label: "B",
      value: "34",
    },
    35: {
      label: "C",
      value: "35",
    },
    36: {
      label: "D",
      value: "36",
    },
    37: {
      label: "E",
      value: "37",
    },
    38: {
      label: "A",
      value: "38",
    },
    39: {
      label: "B",
      value: "39",
    },
    40: {
      label: "C",
      value: "40",
    },
    41: {
      label: "D",
      value: "41",
    },
    42: {
      label: "E",
      value: "42",
    },
    43: {
      label: "A",
      value: "43",
    },
    44: {
      label: "B",
      value: "44",
    },
    45: {
      label: "C",
      value: "45",
    },
    46: {
      label: "D",
      value: "46",
    },
    47: {
      label: "E",
      value: "47",
    },
    48: {
      label: "A",
      value: "48",
    },
    49: {
      label: "B",
      value: "49",
    },
    50: {
      label: "C",
      value: "50",
    },
    51: {
      label: "D",
      value: "51",
    },
    52: {
      label: "E",
      value: "52",
    },
  },
};

const groupTeethByQuadrant = (teethData) => {
  const groupedTeeth = {
    UL: [],
    UR: [],
    BL: [],
    BR: [],
  };

  teethData.forEach((tooth) => {
    const quadrant = tooth.label.substring(0, 2);
    groupedTeeth[quadrant].push(tooth);
  });

  return groupedTeeth;
};

const extractLabelsAndValues = (teethChart) => {
  const data = [];

  // Extract labels and values for each quadrant and tooth
  ["q1", "q2", "q3", "q4"].forEach((quadrant) => {
    teethChart[quadrant].value.forEach((toothId) => {
      const tooth = teethChart.teethIds[toothId];
      data.push({
        quadrant,
        label: tooth.label,
        value: tooth.value,
      });
    });
  });

  return data;
};
// Example usage:
const extractedData = extractLabelsAndValues(teethChart);
console.log("extractedData", extractedData);
// const groupedTeeth = groupTeethByQuadrant(extractedData);
// console.log(groupedTeeth);

// resultant structure

const teethResultant = {
  UL: [
    { label: "UL1", value: "customValue1" },
    { label: "UL2", value: "customValue2" },
    // ... other teeth in UL
  ],
  UR: [
    { label: "UR1", value: "customValue3" },
    { label: "UR2", value: "customValue4" },
    // ... other teeth in UR
  ],
  BL: [
    // ... other teeth in BL
  ],
  BR: [
    // ... other teeth in BR
  ],
};
