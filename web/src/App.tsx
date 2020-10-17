import { Layout, Switch } from 'antd';
import React, { useState } from 'react';
import './App.css';
import Header from './components/Header';

function App() {
	const [isTurned, setIsTurned] = useState(false);

	return (
		<Layout className='App'>
			<Header isTurned={isTurned} onTurn={setIsTurned} />
			<Layout.Content>Content</Layout.Content>
		</Layout>
	);
}

export default App;
