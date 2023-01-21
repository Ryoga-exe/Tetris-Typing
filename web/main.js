const CANVAS    = {W: 160, H: 144},
      STAGE     = {W: 20,  H: 18},
      FIELD_W   = {W: 10,  H: 18},
      PART_SIZE = 8;
let zoomRate;
let ctx;
const col = [
	"#FFFFFF",
	"#AAAAAA",
	"#555555",
  "#000000"
];
let parts  = new Object();
let stage  = [];
let scenes = new Object();  // シーンごとの Stage にあたるデータ

window.addEventListener("load", async function init() {
  const canvas = document.getElementById("mycanvas");
  ctx = canvas.getContext('2d');
  zoomRate = canvas.clientWidth / CANVAS.W;
  console.log(zoomRate);
  parts = (await (getJSON("https://ryoga-exe.github.io/TetrisTyping-Web.ver/parts.json")));
  scenes = (await (getJSON("https://ryoga-exe.github.io/TetrisTyping-Web.ver/scenes.json")));
  
  /*--- Init Array (Get 20*18) ---*/
  stage = Array(STAGE.W);
  for(let y = 0; y < STAGE.W; y++) {
    stage[y] = new Array(STAGE.H).fill("NONE");
  }
  
  start();
  drawStage();

  
});
// Load JSON files
async function getJSON(fileName) {
  let jsonContent;
  await fetch(fileName).then
    (r => r.text()).then(t => {
      jsonContent = JSON.parse(t);
    });
  return jsonContent;
}

function start() {

}

function mainLoop() {
  
}

function drawPart(_x, _y, _part) {
  ctx.fillStyle = "#FF0000";
	for (let i = 0; i < PART_SIZE; i++)
		for (let j = 0; j < PART_SIZE; j++){
      ctx.fillStyle = col[_part[j][i]];
      ctx.fillRect(_x + i * (zoomRate), _y + j * (zoomRate), zoomRate + 1, zoomRate + 1);
    }
}

function drawStage(){
  for (let i = 0; i < STAGE.H; i++)
		for (let j = 0; j < STAGE.W; j++)
      drawPart(24 * j, 24 * i, parts[stage[j][i]]);
}

function fillStage(_partName){
  for (let i = 0; i < STAGE.H; i++)
    for (let j = 0; j < STAGE.W; j++)
      stage[j][i] = _partName;
}