import { Layout, Switch } from 'antd';
import React, { useEffect, useState } from 'react';
import './App.css';
import Header from './components/Header';
import LightsList from './components/LightsList';
import { types } from 'shared';
import './services/socket';
import { turn } from './services/socket/actions';

function App() {
	const [info, setInfo] = useState<types.Info | null>(null);

	useEffect(() => {
		setGlobalInfo = setInfo as typeof setGlobalInfo;
	}, []);

	return (
		<Layout className='App'>
			{info && (
				<>
					<Header isTurned={info.isTurned} onTurn={turn} />
					<Layout.Content>
						<LightsList lights={info.lights} />
					</Layout.Content>
				</>
			)}
		</Layout>
	);
}

export let setGlobalInfo: (
	info: types.Info | ((prevState: types.Info) => types.Info)
) => void;

export default App;
