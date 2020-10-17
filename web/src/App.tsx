import { Layout, Switch } from 'antd';
import React, { useEffect, useState } from 'react';
import './App.css';
import Header from './components/Header';
import LightsList from './components/LightsList';
import { types } from 'shared';
import './services/socket';

function App() {
	const [isTurned, setIsTurned] = useState(false);

	const [info, setInfo] = useState<types.Info | null>(null);

	useEffect(() => {
		setGlobalInfo = setInfo;
	}, []);

	return (
		<Layout className='App'>
			{info && (
				<>
					<Header isTurned={isTurned} onTurn={setIsTurned} />
					<Layout.Content>
						<LightsList lights={info.lights} />
					</Layout.Content>
				</>
			)}
		</Layout>
	);
}

export let setGlobalInfo: (info: types.Info) => void;

export default App;
