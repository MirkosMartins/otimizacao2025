const x1 = Math.floor(Math.random() * 4);
const y1 = 0;
const x2 = 0;
const y2 = Math.floor(Math.random() * 4);

console.log("x1: ", x1);
console.log("y2: ", y2);

const b = x2 + y2;
console.log("b: ", b);

const a = Math.floor((b + y1) / x1);
console.log("a: ", a);