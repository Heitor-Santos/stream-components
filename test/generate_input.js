import fs from 'fs';

function genereteGraph(numNodes, numEdges){
    const graph = [];
    for (let i = 0; i < numNodes; i++) {
        graph[i]=[];
    }
    
    // Embaralha as arestas para obter uma seleção aleatória
    while(numEdges){
        let i = Math.floor(Math.random() * (numNodes));
        let j = Math.floor(Math.random() * (numNodes));
        if(i!=j && !graph[i].includes(j)){
            graph[i].push(j);
            numEdges--;
        }
    }
    return graph
}

function reversedGraph(graph){
    const reverse=[];
    for(let i=0;i<graph.length;i++){
        reverse[i]=[];
    }
    for(let i=0;i<graph.length;i++){
        for(const k of graph[i]){
            reverse[k].push(i);
        }
    }
    return reverse;
}

// Obter os argumentos da linha de comando
var args = process.argv.slice(2);
//console.log(args)
const graph = genereteGraph(args[0], args[1]);
const reverseGraph = reversedGraph(graph);
const nodes = []
const edges = []
for(let i=0; i<graph.length;i++){
    nodes.push({id: i});
    for(let k of graph[i]){
        edges.push({from: i, to: k});
    }
}

function shuffle(lista) {
    for (let i = lista.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [lista[i], lista[j]] = [lista[j], lista[i]];
    }
    return lista;
}

function nodesToRemoveNow(a, b, c) {
    const menor = Math.min(a, b, c);
    return Math.floor(Math.random() * (menor + 1)); 
}

function nodesAleatoriosDoSet(conjunto, quantidade) {
    const elementos = Array.from(conjunto); // Converte o conjunto para um array
    const elementosAleatorios = [];

    // Garante que a quantidade solicitada não seja maior do que o tamanho do conjunto
    quantidade = Math.min(quantidade, elementos.length);

    // Embaralha o array de elementos
    for (let i = elementos.length - 1; i >= 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [elementos[i], elementos[j]] = [elementos[j], elementos[i]];
    }

    // Seleciona os primeiros 'quantidade' elementos do array embaralhado
    for (let i = 0; i < quantidade; i++) {
        elementosAleatorios.push(elementos[i]);
    }

    return elementosAleatorios;
}

const edgesUsed = {}

function getNeighbours(node, graph){
    let neighbours = graph[node];
    // /console.log(neighbours)
    neighbours = neighbours.filter(el=>{
        if(!addedNodes.has(el))return false;
        //console.log("oi "+ node + " "+ el)
        let isUsed = edgesUsed[`${node}-${el}`];
        edgesUsed[`${node}-${el}`] = true;
        edgesUsed[`${el}-${node}`] = true;
        return !isUsed;
    })
    return neighbours
}


function getInEdges(node){
    let inNeighbours = getNeighbours(node, reverseGraph);
    //console.log(inNeighbours)
    //console.log("-000000")
    let inEdges =[]
    for(const neighbour of inNeighbours){
        inEdges.push(`${neighbour} ${node} 5839 8446 4904 R R\n`)
    }
    return inEdges;
}

function getOutEdges(node){
    let outNeighbours = getNeighbours(node, graph);
    let outEdges = []
    for(const neighbour of outNeighbours){
        outEdges.push(`${node} ${neighbour} 5839 8446 4904 R R\n`)
    }
    return outEdges;
}

const lista = Array.from({ length: args[0] }, (_, index) => index);
const shuffleNodes = shuffle(lista);
let nodesToRemove = parseInt(args[2])
let addedNodes = new Set();
const fileInput = `${args[3]}_input`

for(let i of shuffleNodes){
    addedNodes.add(i);
    fs.appendFileSync(fileInput, `${i}\n`);
    const linhaEmBranco = '\n';
    if(nodesToRemove>0){
        let toDelete = nodesToRemoveNow(5, nodesToRemove, addedNodes.size)
        let nodesToDelete =nodesAleatoriosDoSet(addedNodes, toDelete);
        for(const el of nodesToDelete)addedNodes.delete(el);
        fs.appendFileSync(fileInput, nodesToDelete.join(" ")+"\n");   
        nodesToRemove-=toDelete;
    }
    else fs.appendFileSync(fileInput, "\n");
    let incomingEdges= getInEdges(i);
    for(const edge of incomingEdges)fs.appendFileSync(fileInput, edge);
    fs.appendFileSync(fileInput,"edges_end\n");
    let outgoingEdges = getOutEdges(i); 
    for(const edge of outgoingEdges)fs.appendFileSync(fileInput, edge);
    fs.appendFileSync(fileInput,"edges_end\n");
}

if(nodesToRemove>0)console.log("falhou em deletar todos, sobram ",nodesToRemove)
// console.log(args)
// console.log(graph)
// console.log(edgesUsed)
// console.log(getNeighbours( 'h',{'h':['e','i','t','o','r']}))

fs.writeFileSync(`${args[3]}_original_graph.json`, JSON.stringify({nodes, edges}))

