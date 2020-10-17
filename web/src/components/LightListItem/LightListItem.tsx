import { Button, Form, InputNumber, List, TimePicker, Typography } from 'antd';
import React from 'react';
import { interfaces } from 'shared';
import classes from './LightListItem.module.scss';
import moment from 'moment';
import { clamp, setTime, unclamp } from '../../services/socket/actions';

interface Props {
	light: interfaces.ILight;
	canClamp: boolean;
}

const LightListItem = ({ light, canClamp }: Props) => {
	const onChangeTime = (momentDate: moment.Moment | null) => {
		if (!momentDate) throw new Error('Unknown date');
		const time = momentDate.minutes() * 60 + momentDate.seconds();
		setTime(light.id, time);
	};

	return (
		<List.Item className={classes.item}>
			<Typography.Title level={5}>Light</Typography.Title>
			<TimePicker
				showHour={false}
				showNow={false}
				format='mm:ss'
				value={moment(
					`${Math.floor(light.duration / 60)}:${light.duration % 60}`,
					'mm:ss'
				)}
				onChange={onChangeTime}
			/>
			{light.clamped && (
				<Button type='primary' onClick={() => unclamp(light.id)}>
					Unclamp
				</Button>
			)}
			{!light.clamped && (
				<Button disabled={!canClamp} onClick={() => clamp(light.id)}>
					Clamp
				</Button>
			)}
		</List.Item>
	);
};

export default LightListItem;
