import * as dotenv from 'dotenv';

dotenv.config();

import * as express from 'express';
import * as http from 'http';
import { connect as connectSocketIoServer } from './socket.io/socket.io';
import './socket/socket';

const app = express();
const server = http.createServer(app);

const port = process.env.PORT;

connectSocketIoServer(server);

server.listen(port, () => {
	console.log(`Listening ${port} port...`);
});
