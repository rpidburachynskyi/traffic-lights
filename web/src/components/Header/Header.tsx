import { Button, Layout, Switch } from 'antd';
import React from 'react';
import { restart } from '../../services/socket/actions';

import classes from './Header.module.scss';

interface Props {
	isTurned: boolean;
	onTurn: (value: boolean) => void;
}

const Header = ({ isTurned, onTurn }: Props) => {
	return (
		<Layout.Header color='primary' className={classes.header}>
			<div className={classes.content}>
				<Switch
					checkedChildren='On'
					unCheckedChildren='Off'
					checked={isTurned}
					onChange={onTurn}
				/>
				<Button type='primary' size='small' onClick={restart}>
					Restart
				</Button>
			</div>
		</Layout.Header>
	);
};

export default Header;
