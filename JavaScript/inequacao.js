function inequacoes(f, p, tipo) {
    const aux = {
        maior: p.y > (f.a * p.x + f.b),  
        menor: p.y < (f.a * p.x + f.b),  
        igual: p.y === (f.a * p.x + f.b), 
    };

    if (tipo === '<') {
        return aux.menor;  
    } else if (tipo === '<=') {
        return aux.menor || aux.igual;  
    } else if (tipo === '>') {
        return aux.maior;  
    } else if (tipo === '>=') {
        return aux.maior || aux.igual;  
    } else if (tipo === '=') {
        return aux.igual;  
    } else {
        return 'erro';  
    }
}


const retas = { 
    p1: { x: 2, y: 4 }, 
    p2: { x: 5, y: 2 } 
};
const ang = (retas.p2.y - retas.p1.y) / (retas.p2.x - retas.p1.x);
retas.f = { a: ang, b: (retas.p1.y - ang * retas.p1.x) };


let pontos = [{ x: 4, y: 5 }];
const quant = Math.floor(Math.random() * (20 - 4 + 1)) + 4;


/*const pontos = [
    { x: 1, y: 3 },   
    { x: 3, y: 3 },   
    { x: 4, y: 1 },   
    { x: 6, y: 0 },   
]; 

pontos.forEach(ponto => {
    ops.forEach(op => {
        const resultado = inequacoes(retas.f, ponto, op);
        console.log(`Ponto (${ponto.x}, ${ponto.y}) | Inequação '${op}' | Resultado: ${resultado}`);
    });
});*/

const op = '>';  


for (let i = pontos.length; i < quant; i++) {
    pontos.push({ 
        x: Math.floor(Math.random() * (100 - (-100) + 1)) + (-100), 
        y: Math.floor(Math.random() * (100 - (-100) + 1)) + (-100) 
    });
}

console.log(`y ${op} ${retas.f.a} x + (${retas.f.b})`);

for (let i = 0; i < quant; i++) {
    const resultado = inequacoes(retas.f, pontos[i], op);
    console.log(`(${pontos[i].x}, ${pontos[i].y}) : ${resultado}`);
}
