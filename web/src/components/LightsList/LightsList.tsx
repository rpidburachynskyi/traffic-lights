import React from 'react';
import { List } from 'antd';
import { ILight } from '../../interfaces/ILight';
import LightListItem from '../LightListItem';

interface Props {
	lights: ILight[];
}

const LightsList = ({ lights }: Props) => {
	return (
		<List
			dataSource={lights}
			renderItem={(light) => (
				<LightListItem key={light.id} light={light} />
			)}
		/>
	);
};

export default LightsList;
