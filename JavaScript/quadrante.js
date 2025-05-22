function pertenceRegiao(x, y) {
  const cond1 = y >= 0.5 * x + 0;
  const cond2 = y >= -1 * x + 11;
  const cond3 = y <= 10;
  const cond4 = x >= 1;

  return cond1 && cond2 && cond3 && cond4;
}

const pontos = [
  [2, 1],
  [4, 2],
  [1, 10],
  [10, 1],
  [1, 10],
  [2, 10],
  [10, 1],
  [10, 2],
];

pontos.forEach(([x, y]) => {
  const resultado = pertenceRegiao(x, y)
    ? "Pertence a regiao"
    : "Nao pertence a regiao";
  console.log(`Ponto (${x}, ${y}): ${resultado}`);
});
