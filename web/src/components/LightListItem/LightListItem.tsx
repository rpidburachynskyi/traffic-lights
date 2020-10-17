import { Button, Form, InputNumber, List, TimePicker, Typography } from 'antd';
import React from 'react';
import { ILight } from '../../interfaces/ILight';
import classes from './LightListItem.module.scss';

interface Props {
	light: ILight;
}

const LightListItem = ({ light }: Props) => {
	return (
		<List.Item className={classes.item}>
			<Typography.Title level={5}>Light</Typography.Title>
			<TimePicker showHour={false} showNow={false} />
			<Button loading={true}>
				{light.clamped ? 'Clamped' : 'Clamp'}
			</Button>
		</List.Item>
	);
};

export default LightListItem;
