import { Layout, Switch } from 'antd';
import React, { useState } from 'react';
import './App.css';
import Header from './components/Header';
import LightsList from './components/LightsList';
import { ILight } from './interfaces/ILight';
import './services/socket';

function App() {
	const [isTurned, setIsTurned] = useState(false);

	const lights: ILight[] = [
		{
			color: 'black',
			id: 'qwe',
			clamped: true
		}
	];

	return (
		<Layout className='App'>
			<Header isTurned={isTurned} onTurn={setIsTurned} />
			<Layout.Content>
				<LightsList lights={lights} />
			</Layout.Content>
		</Layout>
	);
}

export default App;
