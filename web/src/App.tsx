import { Layout, Switch } from 'antd';
import React, { useEffect, useState } from 'react';
import './App.css';
import Header from './components/Header';
import LightsList from './components/LightsList';
import { types } from 'shared';
import './services/socket';
import { turn } from './services/socket/actions';
import StateViewer from './components/StateViewer';

function App() {
	const [info, setInfo] = useState<types.Info | null>(null);
	const [state, setState] = useState<types.State | null>(null);

	useEffect(() => {
		setGlobalInfo = setInfo as typeof setGlobalInfo;
		setGlobalState = setState as typeof setGlobalState;
	}, []);

	return (
		<Layout className='App'>
			{info && state && (
				<>
					<Header isTurned={info.isTurned} onTurn={turn} />
					<Layout.Content>
						<LightsList lights={info.lights} />
						<StateViewer state={state} />
					</Layout.Content>
				</>
			)}
		</Layout>
	);
}

export let setGlobalInfo: (
	info: types.Info | ((prevInfo: types.Info) => types.Info)
) => void;
export let setGlobalState: (
	state: types.State | ((prevState: types.State) => types.State)
) => void;

export default App;
