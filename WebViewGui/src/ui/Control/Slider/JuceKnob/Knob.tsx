'use client';

import { useState, useEffect } from 'react';

import {
  motion,
  useMotionValue,
  useTransform,
  useDragControls,
  useMotionValueEvent,
} from 'framer-motion';

import Box, { type BoxProps } from '@mui/material/Box';
import Slider, { type SliderProps } from '@mui/material/Slider';

import KnobRail from './KnobRail';
import KnobThumb from './KnobThumb';
import KnobOuter from './KnobOuter';

export interface KnobProps
  extends
  Omit<
    SliderProps,
    | 'value'
    | 'color'
  > {
  value: number;
  dragRange?: number;
  setIsDrag:React.Dispatch<React.SetStateAction<boolean>>;
  color?:string;
  ringColor?: string
}

export type InKnobProps = Omit<
    KnobProps,
    | 'setIsDrag'
  >

function sliderToBox({
  // eslint-disable-next-line @typescript-eslint/no-unused-vars
  defaultValue,
  // eslint-disable-next-line @typescript-eslint/no-unused-vars
  onMouseDown,
  // eslint-disable-next-line @typescript-eslint/no-unused-vars
  onChange,
  // eslint-disable-next-line @typescript-eslint/no-unused-vars
  onChangeCommitted,
  // eslint-disable-next-line @typescript-eslint/no-unused-vars
  scale,
  ...props
}: InKnobProps): BoxProps {
  return {
    ...props,
  };
}

export default function JuceSlider({
  dragRange = 150,
  setIsDrag: setIsDragParent,
  color,
  ringColor='secondary',
  ...props
}: KnobProps) {
  const [isDrag, setIsDrag] = useState(false);
  const handleValue = useMotionValue(props.value * (1 - dragRange));
  const progressScaleValue = useTransform(handleValue, [0, -dragRange], [0, 1]);
  const dragControls = useDragControls();

  useMotionValueEvent(progressScaleValue, 'change', (latest) => {
    if (isDrag && props.onChange) {
      props.onChange(new Event('change'), latest, 0);
    }
  });

  useEffect(() => {
    if (!isDrag) {
      handleValue.set(props.value * (1 - dragRange));
    }
  }, [dragRange, handleValue, isDrag, props.value]);

  return (
    <Box
      {...sliderToBox(props)}
    >
      <Box
        // eslint-disable-next-line @typescript-eslint/no-explicit-any
        onMouseDown={(e: any) => {
          if (props.onMouseDown) {
            props.onMouseDown(e);
          }

          return dragControls.start(e, { snapToCursor: false, distanceThreshold: 0 });
        }}
        sx={{
          position: 'relative',
          width: '100%',
          color: 'var(--mui-palette-primary-main)',
        }}
      >
        <motion.div
          className="handle"
          drag="y"
          dragConstraints={{ top: -dragRange, bottom: 0 }}
          dragControls={dragControls}
          dragMomentum={false}
          onDragStart={() => {
            setIsDrag(true);
            setIsDragParent(true);
          }}
          onDragEnd={(event) => {
            if (props.onChangeCommitted) {
              props.onChangeCommitted(event, progressScaleValue.get());
            }
            setIsDragParent(false);
            setIsDrag(false);
          }}
          style={{
            y: handleValue,
            display: 'none',
          }}
        />

        <svg
          viewBox="20 20 160 165"
        >
          <KnobOuter
            ringColor={ringColor}
          />
          <KnobRail
            color={color}
            ringColor={ringColor}
          />
          <KnobThumb value={props.value} />
        </svg>
      </Box>

      <Slider
        {...props}
        value={props.value}
        sx={{ display: 'none' }}
      />
    </Box>
  );
}
