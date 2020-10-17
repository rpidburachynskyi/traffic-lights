import './socket/socket';
import * as dotenv from 'dotenv';

dotenv.config();

import * as express from 'express';

const app = express();

const port = process.env.PORT || 3000;

app.listen(port, () => console.log(`Listening ${port} port...`));
