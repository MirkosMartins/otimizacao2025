function Ponto(x, y) {
    this.x = x;
    this.y = y;
}

function calculaDistacia(ponto1, ponto2) {
    const dx = ponto2.x - ponto1.x;
    const dy = ponto2.y - ponto1.y;
    return Math.sqrt(dx * dx + dy * dy);
}


function geraAleatorio() {
    return Math.floor(Math.random() * 100);
}

const ponto1 = new Ponto(geraAleatorio(), geraAleatorio());
const ponto2 = new Ponto(geraAleatorio(), geraAleatorio());

const distancia = calculaDistacia(ponto1, ponto2);
console.log(`A distancia e: ${distancia}`)