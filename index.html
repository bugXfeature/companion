<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>COMPANION</title>
  <style>
    @import url('https://fonts.googleapis.com/css2?family=Orbitron:wght@400;700;900&family=Rajdhani:wght@300;400;600&display=swap');

    :root {
      --teal-deep:    #003d40;
      --teal-mid:     #006d75;
      --teal-bright:  #00bcd4;
      --teal-glow:    #00e5ff;
      --metal-light:  #b2dfdb;
      --metal-gold:   #ffd54f;
      --metal-chrome: #e0f7fa;
      --bg:           #000e0f;
      --surface:      #001a1c;
      --border:       rgba(0, 229, 255, 0.15);
    }

    * { margin: 0; padding: 0; box-sizing: border-box; }

    body {
      background: var(--bg);
      color: var(--metal-chrome);
      font-family: 'Rajdhani', sans-serif;
      min-height: 100vh;
      overflow: hidden;
    }

    /* ── Canvas ──────────────────────────────────────────── */
    #canvas3d {
      position: fixed;
      inset: 0;
      z-index: 0;
    }

    /* ── UI overlay ──────────────────────────────────────── */
    #ui {
      position: fixed;
      inset: 0;
      z-index: 10;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: space-between;
      padding: 28px 32px 32px;
      pointer-events: none;
    }

    /* ── Header ──────────────────────────────────────────── */
    header {
      text-align: center;
      pointer-events: none;
    }
    header h1 {
      font-family: 'Orbitron', monospace;
      font-size: clamp(1.1rem, 2.5vw, 1.8rem);
      font-weight: 900;
      letter-spacing: 0.2em;
      color: var(--teal-glow);
      text-shadow: 0 0 20px rgba(0,229,255,0.6), 0 0 40px rgba(0,229,255,0.3);
    }
    header p {
      font-size: 0.75rem;
      letter-spacing: 0.3em;
      color: var(--teal-mid);
      margin-top: 4px;
      text-transform: uppercase;
    }

    /* ── Center mic area ─────────────────────────────────── */
    #center {
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 18px;
      pointer-events: all;
    }

    #mic-btn {
      width: 90px;
      height: 90px;
      border-radius: 50%;
      border: 2px solid var(--teal-glow);
      background: rgba(0, 188, 212, 0.08);
      cursor: pointer;
      display: flex;
      align-items: center;
      justify-content: center;
      transition: all 0.3s ease;
      position: relative;
      backdrop-filter: blur(8px);
      box-shadow: 0 0 20px rgba(0,229,255,0.2), inset 0 0 20px rgba(0,229,255,0.05);
    }
    #mic-btn:hover {
      background: rgba(0, 188, 212, 0.18);
      box-shadow: 0 0 40px rgba(0,229,255,0.5), inset 0 0 30px rgba(0,229,255,0.1);
      transform: scale(1.05);
    }
    #mic-btn.listening {
      background: rgba(0, 229, 255, 0.15);
      border-color: var(--metal-gold);
      box-shadow: 0 0 50px rgba(255,213,79,0.4), inset 0 0 30px rgba(255,213,79,0.08);
      animation: pulse-ring 1.2s ease-in-out infinite;
    }
    @keyframes pulse-ring {
      0%, 100% { box-shadow: 0 0 50px rgba(255,213,79,0.4), inset 0 0 30px rgba(255,213,79,0.08); }
      50%       { box-shadow: 0 0 80px rgba(255,213,79,0.7), inset 0 0 40px rgba(255,213,79,0.15); }
    }
    #mic-btn svg {
      width: 36px; height: 36px;
      transition: all 0.3s;
    }
    #mic-btn.listening svg { stroke: var(--metal-gold); }

    /* ── Transcript ───────────────────────────────────────── */
    #transcript-box {
      background: rgba(0, 26, 28, 0.75);
      border: 1px solid var(--border);
      border-radius: 12px;
      padding: 12px 20px;
      min-width: 280px;
      max-width: 420px;
      text-align: center;
      backdrop-filter: blur(12px);
    }
    #transcript-label {
      font-size: 0.6rem;
      letter-spacing: 0.35em;
      color: var(--teal-mid);
      text-transform: uppercase;
      margin-bottom: 5px;
    }
    #transcript-text {
      font-size: 1.05rem;
      font-weight: 600;
      color: var(--metal-chrome);
      min-height: 24px;
      letter-spacing: 0.05em;
    }

    /* ── Status pill ──────────────────────────────────────── */
    #status-pill {
      display: flex;
      align-items: center;
      gap: 8px;
      padding: 6px 16px;
      border-radius: 999px;
      border: 1px solid var(--border);
      background: rgba(0,26,28,0.6);
      font-size: 0.72rem;
      letter-spacing: 0.2em;
      text-transform: uppercase;
      backdrop-filter: blur(8px);
      transition: all 0.4s;
    }
    #status-dot {
      width: 8px; height: 8px;
      border-radius: 50%;
      background: var(--teal-mid);
      transition: all 0.4s;
    }
    #status-pill.connected #status-dot { background: #69f0ae; box-shadow: 0 0 8px #69f0ae; }
    #status-pill.triggered #status-dot { background: var(--metal-gold); box-shadow: 0 0 8px var(--metal-gold); animation: blink 0.5s infinite; }
    #status-pill.stopped   #status-dot { background: #ef5350; box-shadow: 0 0 8px #ef5350; }
    @keyframes blink { 50% { opacity: 0; } }

    /* ── Bottom controls ──────────────────────────────────── */
    #bottom {
      width: 100%;
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 14px;
      pointer-events: all;
    }

    /* IP input row */
    #ip-row {
      display: flex;
      align-items: center;
      gap: 10px;
      background: rgba(0,26,28,0.7);
      border: 1px solid var(--border);
      border-radius: 10px;
      padding: 8px 14px;
      backdrop-filter: blur(10px);
    }
    #ip-label {
      font-size: 0.65rem;
      letter-spacing: 0.25em;
      color: var(--teal-mid);
      text-transform: uppercase;
      white-space: nowrap;
    }
    #ip-input {
      background: transparent;
      border: none;
      outline: none;
      color: var(--teal-glow);
      font-family: 'Orbitron', monospace;
      font-size: 0.8rem;
      width: 160px;
      letter-spacing: 0.1em;
    }
    #ip-input::placeholder { color: rgba(0,229,255,0.3); }
    #connect-btn {
      background: rgba(0,188,212,0.12);
      border: 1px solid var(--teal-bright);
      color: var(--teal-glow);
      border-radius: 6px;
      padding: 5px 14px;
      cursor: pointer;
      font-family: 'Orbitron', monospace;
      font-size: 0.65rem;
      letter-spacing: 0.15em;
      transition: all 0.3s;
    }
    #connect-btn:hover {
      background: rgba(0,188,212,0.25);
      box-shadow: 0 0 14px rgba(0,229,255,0.3);
    }

    /* Keyword chips */
    #keywords-row {
      display: flex;
      gap: 8px;
      flex-wrap: wrap;
      justify-content: center;
    }
    .kw-chip {
      padding: 4px 12px;
      border-radius: 999px;
      border: 1px solid rgba(0,229,255,0.2);
      background: rgba(0,61,64,0.5);
      font-size: 0.65rem;
      letter-spacing: 0.15em;
      color: var(--teal-bright);
      text-transform: uppercase;
    }
    .kw-chip.stop { border-color: rgba(239,83,80,0.3); color: #ef9a9a; background: rgba(50,10,10,0.4); }

    /* ── Grid lines BG ───────────────────────────────────── */
    #grid-bg {
      position: fixed;
      inset: 0;
      z-index: 1;
      pointer-events: none;
      background:
        linear-gradient(rgba(0,229,255,0.03) 1px, transparent 1px),
        linear-gradient(90deg, rgba(0,229,255,0.03) 1px, transparent 1px);
      background-size: 60px 60px;
      mask-image: radial-gradient(ellipse at center, transparent 30%, black 80%);
    }
  </style>
</head>
<body>

<canvas id="canvas3d"></canvas>
<div id="grid-bg"></div>

<div id="ui">
  <!-- Header -->
  <header>
    <h1>COMPANION</h1>
    <p>3D Audio · WebSocket · Keyword Recognition</p>
  </header>

  <!-- Center: mic + transcript + status -->
  <div id="center">
    <div id="status-pill">
      <div id="status-dot"></div>
      <span id="status-text">Not Connected</span>
    </div>

    <button id="mic-btn" title="Hold to speak">
      <svg viewBox="0 0 24 24" fill="none" stroke="var(--teal-glow)" stroke-width="1.8"
           stroke-linecap="round" stroke-linejoin="round">
        <rect x="9" y="2" width="6" height="12" rx="3"/>
        <path d="M5 10a7 7 0 0 0 14 0"/>
        <line x1="12" y1="19" x2="12" y2="22"/>
        <line x1="9"  y1="22" x2="15" y2="22"/>
      </svg>
    </button>

    <div id="transcript-box">
      <div id="transcript-label">Transcript</div>
      <div id="transcript-text">—</div>
    </div>
  </div>

  <!-- Bottom: IP + keywords -->
  <div id="bottom">
    <div id="ip-row">
      <span id="ip-label">ESP32 IP</span>
      <input id="ip-input" type="text" placeholder="192.168.x.x" spellcheck="false" />
      <button id="connect-btn">CONNECT</button>
    </div>
    <div id="keywords-row">
      <span class="kw-chip">wallet</span>
      <span class="kw-chip">keys</span>
      <span class="kw-chip">medicine</span>
      <span class="kw-chip">spectacles</span>
      <span class="kw-chip">stick</span>
      <span class="kw-chip">watch</span>
      <span class="kw-chip stop">stop · silence · off</span>
    </div>
  </div>
</div>

<!-- ─── Three.js ─────────────────────────────────────────── -->
<script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js"></script>
<script>
// ════════════════════════════════════════════════════════════
//  3D AUDIO VISUALIZER  (Perlin-noise blob + post-glow)
// ════════════════════════════════════════════════════════════

const canvas = document.getElementById('canvas3d');
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true, alpha: true });
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setClearColor(0x000e0f, 1);

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(50, window.innerWidth / window.innerHeight, 0.1, 100);
camera.position.set(0, 0, 18);

// ── Analyser setup ────────────────────────────────────────
let analyser = null, dataArray = null, audioCtx = null, micStream = null;

async function initAudio() {
  audioCtx = new (window.AudioContext || window.webkitAudioContext)();
  const stream = await navigator.mediaDevices.getUserMedia({ audio: true });
  micStream = stream;
  const source = audioCtx.createMediaStreamSource(stream);
  analyser = audioCtx.createAnalyser();
  analyser.fftSize = 256;
  source.connect(analyser);
  dataArray = new Uint8Array(analyser.frequencyBinCount);
}

function getAudioLevel() {
  if (!analyser) return 0;
  analyser.getByteFrequencyData(dataArray);
  let sum = 0;
  for (let i = 0; i < dataArray.length; i++) sum += dataArray[i];
  return sum / (dataArray.length * 255);
}

// ── Blob sphere ───────────────────────────────────────────
const vertShader = `
  uniform float u_time;
  uniform float u_intensity;
  varying vec3 vNormal;
  varying float vNoise;

  // Classic Perlin 3D
  vec3 mod289(vec3 x){ return x - floor(x*(1./289.))*289.; }
  vec4 mod289(vec4 x){ return x - floor(x*(1./289.))*289.; }
  vec4 permute(vec4 x){ return mod289(((x*34.)+10.)*x); }
  vec4 taylorInvSqrt(vec4 r){ return 1.79284291400159 - 0.85373472095314*r; }
  vec3 fade(vec3 t){ return t*t*t*(t*(t*6.-15.)+10.); }

  float pnoise(vec3 P, vec3 rep){
    vec3 Pi0=mod(floor(P),rep), Pi1=mod(Pi0+vec3(1.),rep);
    Pi0=mod289(Pi0); Pi1=mod289(Pi1);
    vec3 Pf0=fract(P), Pf1=Pf0-vec3(1.);
    vec4 ix=vec4(Pi0.x,Pi1.x,Pi0.x,Pi1.x);
    vec4 iy=vec4(Pi0.yy,Pi1.yy);
    vec4 iz0=Pi0.zzzz, iz1=Pi1.zzzz;
    vec4 ixy=permute(permute(ix)+iy);
    vec4 ixy0=permute(ixy+iz0), ixy1=permute(ixy+iz1);
    vec4 gx0=ixy0*(1./7.), gy0=fract(floor(gx0)*(1./7.))-.5;
    gx0=fract(gx0);
    vec4 gz0=vec4(.5)-abs(gx0)-abs(gy0);
    vec4 sz0=step(gz0,vec4(0.));
    gx0-=sz0*(step(vec4(0.),gx0)-.5);
    gy0-=sz0*(step(vec4(0.),gy0)-.5);
    vec4 gx1=ixy1*(1./7.), gy1=fract(floor(gx1)*(1./7.))-.5;
    gx1=fract(gx1);
    vec4 gz1=vec4(.5)-abs(gx1)-abs(gy1);
    vec4 sz1=step(gz1,vec4(0.));
    gx1-=sz1*(step(vec4(0.),gx1)-.5);
    gy1-=sz1*(step(vec4(0.),gy1)-.5);
    vec3 g000=vec3(gx0.x,gy0.x,gz0.x), g100=vec3(gx0.y,gy0.y,gz0.y);
    vec3 g010=vec3(gx0.z,gy0.z,gz0.z), g110=vec3(gx0.w,gy0.w,gz0.w);
    vec3 g001=vec3(gx1.x,gy1.x,gz1.x), g101=vec3(gx1.y,gy1.y,gz1.y);
    vec3 g011=vec3(gx1.z,gy1.z,gz1.z), g111=vec3(gx1.w,gy1.w,gz1.w);
    vec4 norm0=taylorInvSqrt(vec4(dot(g000,g000),dot(g010,g010),dot(g100,g100),dot(g110,g110)));
    g000*=norm0.x; g010*=norm0.y; g100*=norm0.z; g110*=norm0.w;
    vec4 norm1=taylorInvSqrt(vec4(dot(g001,g001),dot(g011,g011),dot(g101,g101),dot(g111,g111)));
    g001*=norm1.x; g011*=norm1.y; g101*=norm1.z; g111*=norm1.w;
    float n000=dot(g000,Pf0), n100=dot(g100,vec3(Pf1.x,Pf0.yz));
    float n010=dot(g010,vec3(Pf0.x,Pf1.y,Pf0.z)), n110=dot(g110,vec3(Pf1.xy,Pf0.z));
    float n001=dot(g001,vec3(Pf0.xy,Pf1.z)), n101=dot(g101,vec3(Pf1.x,Pf0.y,Pf1.z));
    float n011=dot(g011,vec3(Pf0.x,Pf1.yz)), n111=dot(g111,Pf1);
    vec3 fade_xyz=fade(Pf0);
    vec4 n_z=mix(vec4(n000,n100,n010,n110),vec4(n001,n101,n011,n111),fade_xyz.z);
    vec2 n_yz=mix(n_z.xy,n_z.zw,fade_xyz.y);
    return 2.2*mix(n_yz.x,n_yz.y,fade_xyz.x);
  }

  void main(){
    vNormal = normalize(normalMatrix * normal);
    float noise = pnoise(position * 0.35 + u_time * 0.25, vec3(10.0));
    float displacement = noise * (0.55 + u_intensity * 2.2);
    vNoise = displacement;
    vec3 newPos = position + normal * displacement;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(newPos, 1.0);
  }
`;

const fragShader = `
  uniform float u_time;
  uniform float u_intensity;
  varying vec3 vNormal;
  varying float vNoise;

  void main(){
    // Deep teal base → bright metallic on peaks
    vec3 colLow  = vec3(0.0, 0.24, 0.25);   // deep teal
    vec3 colMid  = vec3(0.0, 0.73, 0.83);   // bright cyan
    vec3 colHigh = vec3(0.88, 0.96, 1.0);   // near-white metallic
    vec3 colAudio= vec3(1.0, 0.84, 0.31);   // gold on loud audio

    float t = clamp(vNoise * 1.5 + 0.5, 0.0, 1.0);
    vec3 baseColor = mix(colLow, colMid, t);
    baseColor = mix(baseColor, colHigh, t * t);
    baseColor = mix(baseColor, colAudio, u_intensity * 0.8);

    // Rim lighting
    float rim = 1.0 - abs(dot(vNormal, vec3(0., 0., 1.)));
    rim = pow(rim, 3.0);
    baseColor += rim * vec3(0.0, 0.9, 1.0) * 0.6;

    gl_FragColor = vec4(baseColor, 0.92);
  }
`;

const uniforms = {
  u_time:      { value: 0 },
  u_intensity: { value: 0 }
};

const mat = new THREE.ShaderMaterial({
  vertexShader: vertShader,
  fragmentShader: fragShader,
  uniforms,
  wireframe: true
});

const geo  = new THREE.IcosahedronGeometry(4, 30);
const blob = new THREE.Mesh(geo, mat);
scene.add(blob);

// ── Ambient ring particles ────────────────────────────────
const ringGeo = new THREE.BufferGeometry();
const PCOUNT  = 800;
const pos     = new Float32Array(PCOUNT * 3);
for (let i = 0; i < PCOUNT; i++) {
  const theta = Math.random() * Math.PI * 2;
  const phi   = Math.random() * Math.PI;
  const r     = 5.5 + Math.random() * 3;
  pos[i*3]   = r * Math.sin(phi) * Math.cos(theta);
  pos[i*3+1] = r * Math.sin(phi) * Math.sin(theta);
  pos[i*3+2] = r * Math.cos(phi);
}
ringGeo.setAttribute('position', new THREE.BufferAttribute(pos, 3));
const ringMat  = new THREE.PointsMaterial({ color: 0x00e5ff, size: 0.06, transparent: true, opacity: 0.5 });
const particles = new THREE.Points(ringGeo, ringMat);
scene.add(particles);

// ── Clock ─────────────────────────────────────────────────
const clock = new THREE.Clock();
let targetIntensity = 0;

function animate() {
  const t = clock.getElapsedTime();
  const audio = getAudioLevel();
  targetIntensity += (audio - targetIntensity) * 0.12;

  uniforms.u_time.value      = t;
  uniforms.u_intensity.value = targetIntensity;

  blob.rotation.y = t * 0.08;
  blob.rotation.x = t * 0.04;
  particles.rotation.y = -t * 0.03;

  // Pulse particles on audio
  ringMat.opacity = 0.35 + targetIntensity * 0.6;
  ringMat.size    = 0.05 + targetIntensity * 0.12;

  renderer.render(scene, camera);
  requestAnimationFrame(animate);
}
animate();

window.addEventListener('resize', () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});


// ════════════════════════════════════════════════════════════
//  BUZZER CONFIG + SPEECH (HTTP-based, continuous listening)
// ════════════════════════════════════════════════════════════

const BUZZERS = [
  { endpoint: '/buzz/0', keyword: 'wallet',
    aliases: ['wallet', 'wallets', 'walled', 'ballet', 'valet'] },
  { endpoint: '/buzz/1', keyword: 'keys',
    aliases: ['keys', 'key', 'cheese', 'please keys'] },
  { endpoint: '/buzz/2', keyword: 'medicine',
    aliases: ['medicine', 'medicines', 'medical', 'medic'] },
  { endpoint: '/buzz/3', keyword: 'spectacles',
    aliases: ['spectacles', 'spectacle', 'spect', 'specs', 'glasses'] },
  { endpoint: '/buzz/4', keyword: 'stick',
    aliases: ['stick', 'sticks', 'stick'] },
  { endpoint: '/buzz/5', keyword: 'watch',
    aliases: ['watch', 'watches', 'watched'] },
];

// Stop words — any of these kills the buzzer
const STOP_WORDS = ['stop', 'silence', 'off', 'quiet', 'enough', 'shut'];

const ipInput      = document.getElementById('ip-input');
const connectBtn   = document.getElementById('connect-btn');
const statusPill   = document.getElementById('status-pill');
const statusText   = document.getElementById('status-text');
const transcriptEl = document.getElementById('transcript-text');
const micBtn       = document.getElementById('mic-btn');

// Load saved IP
const savedIP = localStorage.getItem('espIP');
if (savedIP) ipInput.value = savedIP;

const ESP_PORT = 81;  // must match the port in esp32_buzzer.ino
function getESPIP() { return ipInput.value.trim() || '192.168.1.100'; }
function espURL(path) { return `http://${getESPIP()}:${ESP_PORT}${path}`; }

function setStatus(cls, text) {
  statusPill.className = cls;
  statusText.textContent = text;
}

// CONNECT button just saves the IP and marks as ready
connectBtn.addEventListener('click', () => {
  const ip = getESPIP();
  if (!ip) return;
  localStorage.setItem('espIP', ip);
  setStatus('connected', `Ready · ${ip}`);
});

// ── Trigger a buzzer via HTTP GET (fire-and-forget) ───────
function triggerBuzzer(index) {
  const b   = BUZZERS[index];
  const url = espURL(b.endpoint);
  setStatus('triggered', `Buzzing · ${b.keyword}`);
  fetch(url, { mode: 'no-cors' })
    .then(() => console.log(`✔ Triggered ${b.keyword}`))
    .catch(err => {
      console.warn(`✘ ${b.keyword} failed:`, err);
      setStatus('', `Error: ${err.message}`);
    });
}

// ── Send stop command (fire-and-forget) ───────────────────
function stopBuzzers() {
  const url = espURL('/stop');
  setStatus('stopped', 'Buzzer Stopped');
  fetch(url, { mode: 'no-cors' })
    .then(() => console.log('✔ Stop sent'))
    .catch(err => console.warn('✘ Stop failed:', err));
  setTimeout(() => setStatus('connected', `Ready · ${getESPIP()}`), 1500);
}

// ══════════════════════════════════════════════════════════════
//  SPEECH ENGINE  —  zero-delay, pre-indexed keyword matching
// ══════════════════════════════════════════════════════════════
const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition;
let recognition = null;
let isListening = false;

// ── Build a lookup map:  heard-word → { type, index } ────────
// Every alias maps to { type:'buzz', index } or { type:'stop' }
// so matching is a single Map.get() — O(1), no loops.
const WORD_MAP = new Map();

// Stop words
['stop', 'silence', 'off', 'quiet', 'enough', 'shut'].forEach(w =>
  WORD_MAP.set(w, { type: 'stop' })
);

// Buzzer aliases  (index matches BUZZERS array)
const ALIAS_TABLE = [
  /* 0 wallet     */ ['wallet', 'wallets', 'walled', 'ballet', 'valet'],
  /* 1 keys       */ ['keys', 'key', 'cheese'],
  /* 2 medicine   */ ['medicine', 'medicines', 'medical', 'medic'],
  /* 3 spectacles */ ['spectacles', 'spectacle', 'spect', 'specs', 'glasses'],
  /* 4 stick      */ ['stick', 'sticks'],
  /* 5 watch      */ ['watch', 'watches', 'watched'],
];
ALIAS_TABLE.forEach((words, idx) =>
  words.forEach(w => WORD_MAP.set(w, { type: 'buzz', index: idx }))
);

// Debounce per-action (allows instant switching between different keywords)
let lastAction = { key: '', time: 0 };

function handleTranscript(text) {
  const now  = Date.now();
  const words = text.toLowerCase().split(/[\s,;.!?''']+/);

  for (const w of words) {
    const hit = WORD_MAP.get(w);
    if (!hit) continue;

    // Debounce: block the SAME action within 700 ms
    const actionKey = hit.type === 'stop' ? '__stop' : `buzz_${hit.index}`;
    if (actionKey === lastAction.key && now - lastAction.time < 700) continue;

    lastAction = { key: actionKey, time: now };

    if (hit.type === 'stop') {
      stopBuzzers();
    } else {
      triggerBuzzer(hit.index);
    }
    return;  // one action per transcript chunk
  }
}

function createRecognition() {
  const rec = new SpeechRecognition();
  rec.continuous     = true;
  rec.interimResults = true;
  rec.lang           = 'en-US';
  rec.maxAlternatives = 1;

  rec.onresult = (e) => {
    let text = '';
    for (let i = e.resultIndex; i < e.results.length; i++) {
      text += e.results[i][0].transcript + ' ';
    }
    transcriptEl.textContent = text.trim() || '—';
    handleTranscript(text);
  };

  rec.onerror = (e) => {
    console.warn('Speech error:', e.error);
    if (e.error === 'not-allowed' || e.error === 'service-not-allowed') {
      setStatus('', 'Mic access denied');
      isListening = false;
      micBtn.classList.remove('listening');
    }
    // no-speech, network, aborted → onend will restart
  };

  rec.onend = () => {
    if (isListening) {
      // Instant restart — no setTimeout delay
      try { rec.start(); } catch(_) {
        // If instant restart fails (Chrome throttle), retry after 50 ms
        setTimeout(() => { if (isListening) try { rec.start(); } catch(_) {} }, 50);
      }
    } else {
      micBtn.classList.remove('listening');
    }
  };

  return rec;
}

micBtn.addEventListener('click', async () => {
  // Init audio visualizer on first click
  if (!audioCtx) {
    try { await initAudio(); } catch(e) { console.warn('Audio init:', e); }
  }

  if (!SpeechRecognition) {
    alert('Speech Recognition not supported. Use Chrome.');
    return;
  }

  if (!isListening) {
    isListening = true;
    recognition = createRecognition();   // fresh instance every time
    micBtn.classList.add('listening');
    transcriptEl.textContent = 'Listening…';
    setStatus('connected', `Ready · ${getESPIP()}`);
    try { recognition.start(); } catch(_) {}
  } else {
    isListening = false;
    if (recognition) { try { recognition.abort(); } catch(_) {} }  // abort = instant kill
    micBtn.classList.remove('listening');
    transcriptEl.textContent = '—';
    setStatus('', 'Not Connected');
  }
});
</script>
</body>
</html>
