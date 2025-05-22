function inequacoes(f, p, tipo) {
  const yFunc = f.a * p.x + f.b;
  const aux = {
    menor: p.y < yFunc,
    menor_igual: p.y <= yFunc,
    maior: p.y > yFunc,
    maior_igual: p.y >= yFunc,
    igual: p.y === yFunc,
  };

  switch (tipo) {
    case "<":
      return aux.menor;
    case "<=":
      return aux.menor_igual;
    case ">":
      return aux.maior;
    case ">=":
      return aux.maior_igual;
    default:
      return false;
  }
}

const func = { a: 2, b: 1 };
const sinal = ">=";

const pontos = [
  { x: 2, y: 6 },
  { x: -3, y: 4 },
  { x: -2, y: 3 },
  { x: 4, y: -2 },
];

console.log(`Equação da reta: y = ${func.a}x + ${func.b}`);
console.log(`Inequação: y ${sinal} ${func.a}x + ${func.b}\n`);

pontos.forEach((p) => {
  const res = inequacoes(func, p, sinal);
  console.log(`Ponto (${p.x}, ${p.y}) -> ${res ? "Satisfaz" : "Não satisfaz"}`);
});
