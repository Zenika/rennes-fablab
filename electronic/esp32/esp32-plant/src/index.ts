import express, { json, Request, Response } from 'express';
import WebSocket, { WebSocketServer } from 'ws';

let websockets: WebSocket[] = [];
const app = express();
app.use(json());

app.use((err: unknown, req: Request, res: Response, next: () => void) => {
  if (err instanceof SyntaxError && (err as any).status === 400 && 'body' in err) {
    console.error(err);
    return res.status(400).send({ status: 404, message: err.message });
  }
  next();
});

const port = 3000;

function logRequest(req: Request) {
  console.log(`${req.method} / called by ${req.ip} with user agent : ${req.headers['user-agent']} and Content-Type: ${req.headers['content-type']}`);
  if (req.body) {
    console.log('---BODY---')
    console.log(req.body);
    console.log('----------')
  }
}

app.get('/', (req: Request, res: Response) => {
  logRequest(req);
  res.send('OK');
});

app.post('/', (req: Request, res: Response) => {
  logRequest(req);
  res.send('OK');
});

app.post('/sensor', (req: Request, res: Response) => {
  logRequest(req);
  res.send('OK');
  websockets.forEach((ws: WebSocket) => ws.send(JSON.stringify(req.body)));
});

app.listen(port, () => {
  console.log(`Server listening on port ${port}`);
});

const wss = new WebSocketServer({
  port: 8081,
});

wss.on('connection', function connection(ws) {
  console.log('New websocket connected');

  ws.on('error', console.error);

  ws.on('message', function message(data) {
    console.log('received: %s', data);
  });

  ws.on('close', () => {
    console.log('Websocket closed');
    websockets = websockets.filter((socket) => socket !== ws);
  });

  websockets.push(ws);
});