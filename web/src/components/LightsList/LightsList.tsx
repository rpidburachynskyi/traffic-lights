import React from 'react';
import { List } from 'antd';
import LightListItem from '../LightListItem';
import { interfaces } from 'shared';

interface Props {
	lights: interfaces.ILight[];
}

const LightsList = ({ lights }: Props) => {
	const isAnyoneClamped = !!lights.find((l) => l.clamped);

	return (
		<List
			dataSource={lights}
			renderItem={(light) => (
				<LightListItem
					key={light.id}
					light={light}
					canClamp={!isAnyoneClamped}
				/>
			)}
		/>
	);
};

export default LightsList;
