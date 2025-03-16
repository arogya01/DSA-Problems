const { MongoClient, ObjectId } = require("mongodb");
const fs = require("fs");
const path = require("path");

const MasterPlanEnum = {
  DEMO: "DEMO",
  PLAT04A: "PLAT04A",
  PLAT04B: "PLAT04B",
  PLAT006A: "PLAT006A",
  PLAT006B: "PLAT006B",
  PLAT04C: "PLAT04C",
  PLAT04D: "PLAT04D",
  PLAT006C: "PLAT006C",
  PLAT006D: "PLAT006D",
  INDE01: "INDE01",
  SECARE01: "SECARE01",
  SABHA01: "SABHA01",
};

const MASTER_PLAN_STATIC = {
  [MasterPlanEnum.PLAT04A]: {
    planName: "Essential",
    userLimit: 3,
    bulkSms: true,
    successManager: true,
  },
  [MasterPlanEnum.PLAT04B]: {
    planName: "Essential Rx",
    userLimit: 3,
    bulkSms: true,
    successManager: true,
    specialisedEmr: true,
  },
  [MasterPlanEnum.PLAT006A]: {
    planName: "Advanced",
    userLimit: 3,
    bulkSms: true,
    successManager: true,
    gmb: true,
    emiFinancing: true,
    verifiedWhatsappAccount: true,
    indemnityInsurance: true,
    smartVitals: true,
    riders: ["DRXWABARIDER01", "GMB01", "SMARTVITAL01"],
  },
  [MasterPlanEnum.PLAT006B]: {
    planName: "Advanced Rx",
    userLimit: 3,
    bulkSms: true,
    successManager: true,
    gmb: true,
    emiFinancing: true,
    verifiedWhatsappAccount: true,
    indemnityInsurance: true,
    smartVitals: true,
    specialisedEmr: true,
    riders: ["DRXWABARIDER01", "GMB01", "SMARTVITAL01"],
  },
  [MasterPlanEnum.PLAT04C]: {
    planName: "Professional",
    userLimit: 3,
    bulkSms: true,
    successManager: true,
    connectionAdvantage: 6999,
  },
  [MasterPlanEnum.PLAT04D]: {
    planName: "Professional Rx",
    userLimit: 3,
    bulkSms: true,
    successManager: true,
    connectionAdvantage: 6999,
    specialisedEmr: true,
  },
  [MasterPlanEnum.PLAT006C]: {
    planName: "Elite",
    userLimit: 3,
    gmb: true,
    emiFinancing: true,
    connectionAdvantage: 6999,
    bulkSms: true,
    successManager: true,
    riders: ["GMB01"],
  },
  [MasterPlanEnum.PLAT006D]: {
    planName: "Elite RX",
    userLimit: 3,
    gmb: true,
    emiFinancing: true,
    connectionAdvantage: 6999,
    bulkSms: true,
    successManager: true,
    specialisedEmr: true,
    riders: ["GMB01"],
  },
  [MasterPlanEnum.INDE01]: {
    planName: "Practice Management Software",
    userLimit: 3,
    bulkSms: true,
    successManager: true,
    specialisedEmr: true,
  },
  [MasterPlanEnum.SABHA01]: {
    planName: "Select E-Care",
    userLimit: 3,
    gmb: true,
    emiFinancing: true,
    connectionAdvantage: 6999,
    bulkSms: true,
    successManager: true,
    specialisedEmr: true,
  },
  [MasterPlanEnum.SECARE01]: {
    planName: "Select ABHA Elite",
    userLimit: 3,
    connectionAdvantage: 6999,
    bulkSms: true,
    successManager: true,
  },
};

async function writeToLog(logStream, message) {
  const timestamp = new Date().toISOString();
  logStream.write(`${timestamp}: ${message}\n`);
}



// different condtions are more like: 
// 1. if plan contains existing riders 
// 2. if plan does not contain existing riders 
// 3. if whatsapp is already present then, that guy shouldn't be pushed again

async function migrateData(dryRun = true) {
  const logFilePath = path.join(__dirname, "migration.log");
  const logStream = fs.createWriteStream(logFilePath, { flags: "a" });

  const client = new MongoClient(
    "mongodb://drxauth:gtB3srIv0C4BHtYxZGpC@Mongouatpublic2.healthrx.co.in:27017/?directConnection=true&authMechanism=SCRAM-SHA-1&tls=false&authSource=drxauth"
  );

  try {
    const startTime = Date.now();
    await client.connect();
    await writeToLog(logStream, "Connected to MongoDB");

    const db = client.db("drxauth");
    const collection = db.collection("authority");

    // Query documents with masterPlan
    const documents = collection.find({
      masterPlan: { $exists: true, $ne: {} }
    });

    const updates = [];
    let processedCount = 0;

    let cnt = 0;
    while (await documents.hasNext()) {      
      const doc = await documents.next();
      const productCode = doc.masterPlan?.productCode;      

      if (!productCode || !MASTER_PLAN_STATIC[productCode]) {
        continue;
      }

      if(doc.username !== "nareshjackello") continue;
      const planDetails = MASTER_PLAN_STATIC[productCode];
      const hasGMB = planDetails.gmb === true;
      const hasSmartVitals = planDetails.smartVitals === true;

      // Get existing riderPlans or initialize empty array
      const existingRiderPlans = doc.riderPlans || [];
      const newRiderPlans = [...existingRiderPlans];

      // Add GMB rider if plan has GMB
      if (
        hasGMB &&
        !existingRiderPlans.some((rider) => rider.productCode === "GMB01")
      ) {
        newRiderPlans.push({
          productCode: "GMB01",
          startDate: doc.masterPlan.startDate,
          expiryDate: doc.masterPlan.expiryDate,
          name: "Google My Business Online Reputation Management",
          validTill: doc.masterPlan.validTill,
          linkedPC: doc.masterPlan.productCode,
        });
      }

      // Add SmartVitals rider if plan has SmartVitals
      if (
        hasSmartVitals &&
        !existingRiderPlans.some(
          (rider) => rider.productCode === "SMARTVITAL01"
        )
      ) {
        newRiderPlans.push({
          productCode: "SMARTVITAL01",
          startDate: doc.masterPlan.startDate,
          expiryDate: doc.masterPlan.expiryDate,
          name: "Smart Vital Pro",
          validTill: doc.masterPlan.validTill,
          linkedPC: doc.masterPlan.productCode,
        });
      }

      // Only update if there are changes to riderPlans
      if (newRiderPlans.length > existingRiderPlans.length) {
        updates.push({
          updateOne: {
            filter: { _id: doc._id },
            update: {
              $set: {
                riderPlans: newRiderPlans,
              },
            },
          },
        });
      }
      cnt++;
      processedCount++;
      if (processedCount % 1000 === 0) {
        await writeToLog(logStream, `Processed ${processedCount} documents`);
      }
    }

    if (updates.length > 0) {
      if (dryRun) {
        await writeToLog(
          logStream,
          `Would update ${updates.length} documents (dry run)`
        );
      } else {
        const bulkWriteResult = await collection.bulkWrite(updates);
        await writeToLog(
          logStream,
          `Updated ${bulkWriteResult.modifiedCount} documents`
        );
      }
    }
    const endTime = Date.now();
    const timeTaken = endTime - startTime;
    await writeToLog(logStream, `Migration completed in ${timeTaken}ms`);
  } catch (error) {
    await writeToLog(logStream, `Error: ${error.message}`);
    throw error;
  } finally {
    await client.close();
    await writeToLog(logStream, "Closed MongoDB connection");
    logStream.end();
  }
}

const dryRun = process.argv.includes("--dry-run");
migrateData(dryRun).catch((error) => {
  console.error("Migration failed:", error);
  process.exit(1);
});
