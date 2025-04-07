const fs = require('fs');

function gerarCoordenadasAleatorias(quantidade) {
    const coordenadas = [];
    for (let i = 0; i < quantidade; i++) {
        const x1 = (Math.random() * 200 - 100).toFixed(2);
        const y1 = (Math.random() * 200 - 100).toFixed(2);
        const x2 = (Math.random() * 200 - 100).toFixed(2);
        const y2 = (Math.random() * 200 - 100).toFixed(2);
        coordenadas.push(`(${x1},${y1}),(${x2},${y2})`);
    }
    return coordenadas.join('\n');
}

const caminhoArquivo = 'C:\\Users\\laboratorio\\Downloads\\coordenadas.txt';
const quantidade = 10;

const conteudo = gerarCoordenadasAleatorias(quantidade);
fs.writeFileSync(caminhoArquivo, conteudo, 'utf8');
console.log(`Arquivo "${caminhoArquivo}" gerado com sucesso!`);