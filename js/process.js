const solve = {
    "ProcedureTC-78951": {
        "count": 0,
        "price": 1750,
        "name": "Ni-Cr Metal crown",
        "subvention": 40,
        "code": "TC-78951",
        "maxAmount": 0,
        "category": "INC"
    },
    "ProcedureTC-78952": {
        "count": 0,
        "price": 3250,
        "name": "Co-Cr Metal crown",
        "subvention": 40,
        "code": "TC-78952",
        "maxAmount": 0,
        "category": "INC"
    },
    "ProcedureTC-78953": {
        "count": 0,
        "price": 4500,
        "name": "RFM (Ceramic )",
        "subvention": 40,
        "code": "TC-78953",
        "maxAmount": 0,
        "category": "INC"
    },
    "ProcedureTC-78937": {
        "count": 1,
        "price": 700,
        "name": "GICg",
        "subvention": 40,
        "code": "TC-78937",
        "maxAmount": 0,
        "category": "EXC"
    },
    "ProcedureTC-78938": {
        "count": 0,
        "price": 1000,
        "name": "Silver Filling",
        "subvention": 40,
        "code": "TC-78938",
        "maxAmount": 0,
        "category": "EXC"
    },
    "ProcedureTC-78939": {
        "count": 0,
        "price": 1200,
        "name": "Composite",
        "subvention": 40,
        "code": "TC-78939",
        "maxAmount": 0,
        "category": "EXC"
    }
}; 


const filtered = Object.keys(solve).reduce((acc, key) => {
    if (solve[key].category === 'INC') {
        acc[key] = solve[key];
    }
    return acc;
});

console.log('filtered', filtered); 