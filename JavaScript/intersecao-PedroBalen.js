function calcularIntersecao(x1_r1, y1_r1, x2_r1, y2_r1, x1_r2, y1_r2, x2_r2, y2_r2) {
    let a1, b1;
    if (x1_r1 === x2_r1) {
        a1 = Infinity;
        b1 = x1_r1; 
    } else {
        a1 = (y2_r1 - y1_r1) / (x2_r1 - x1_r1);
        b1 = y1_r1 - a1 * x1_r1;
    }

    let a2, b2;
    if (x1_r2 === x2_r2) {
        a2 = Infinity;
        b2 = x1_r2; 
    } else {
        a2 = (y2_r2 - y1_r2) / (x2_r2 - x1_r2);
        b2 = y1_r2 - a2 * x1_r2;
    }
    
    if (a1 === a2) {
        if (b1 === b2) {
            return "Retas coincidentes (infinitos pontos de intersecao)";
        } else {
            return "Retas paralelas (sem intersecao)";
        }
    } else if (a1 === Infinity) {
        const x = b1;
        const y = a2 * x + b2;
        return `Intersecao no ponto (${x}, ${y})`;
    } else if (a2 === Infinity) {
        const x = b2;
        const y = a1 * x + b1;
        return `Intersecao no ponto (${x}, ${y})`;
    } else {
        const x = (b2 - b1) / (a1 - a2);
        const y = a1 * x + b1;
        return `Intersecao no ponto (${x}, ${y})`;
    }
}

const x1_r1 = 4, y1_r1 = 0, x2_r1 = 0, y2_r1 = 2;
const x1_r2 = 0, y1_r2 = 1, x2_r2 = 1, y2_r2 = 0;

console.log(calcularIntersecao(x1_r1, y1_r1, x2_r1, y2_r1, x1_r2, y1_r2, x2_r2, y2_r2));