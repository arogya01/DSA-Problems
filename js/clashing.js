const dayjs = require('dayjs');

const obj = {
  2: "2023-10-10T18:30:00.000Z",
  3: "2023-10-11T18:30:00.000Z"
};

const priorities = {
  2: { interval: 1, priority: 2 },
  3: { interval: 1, priority: 1 }
};

function checkAndAdjustDates(id, date) {
  const priority = priorities[id].priority;
  const otherIds = Object.keys(obj).filter((key) => key !== id);
  const otherDates = otherIds.map((key) => obj[key]);

  if (otherDates.includes(date)) {
    const otherId = otherIds[otherDates.indexOf(date)];
    const otherPriority = priorities[otherId].priority;

    if (priority > otherPriority) {
      // Push down the date for the id with lower priority
      const newDate = dayjs(date).add(priorities[id].interval, 'day').toISOString();
      obj[id] = newDate;
    } else {
      // Push down the date for the other id with lower priority
      const newDate = dayjs(date).add(priorities[otherId].interval, 'day').toISOString();
      obj[otherId] = newDate;
    }
  } else {
    // No clash, set the date for the given id
    obj[id] = date;
  }
}