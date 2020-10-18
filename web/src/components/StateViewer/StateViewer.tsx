import classes from './StateViewer.module.scss';
import React from 'react';
import { types } from 'shared';

interface Props {
	state: types.State;
}

const StateViewer = ({ state }: Props) => {
	console.log(state);
	return (
		<div className={classes.grid}>
			<div
				className={`${state.redState ? classes.red : classes.noLight} ${
					classes.item
				}`}
			></div>
			<div
				className={`${
					state.yellowState ? classes.yellow : classes.noLight
				} ${classes.item}`}
			></div>
			<div className={classes.lowerGrid}>
				<div
					className={`${
						state.leftGreenState ? classes.green : classes.noLight
					} ${classes.item}`}
				></div>
				<div
					className={`${
						state.greenState ? classes.green : classes.noLight
					} ${classes.item}`}
				></div>
				<div
					className={`${
						state.rightGreenState ? classes.green : classes.noLight
					} ${classes.item}`}
				></div>
			</div>
		</div>
	);
};

export default StateViewer;
