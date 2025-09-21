'use client';

import { useEffect, useMemo, forwardRef } from 'react';
import { useMotionValue, useTransform, useMotionValueEvent } from 'framer-motion';

import KnobRail from './KnobRail';
import KnobThumb from './KnobThumb';
import KnobOuter from './KnobOuter';
import { useDrag } from './useDrag';
import { Box, type BoxProps, type SliderProps } from '@mantine/core';

export interface KnobProps
  extends BoxProps,
    Omit<SliderProps, 'value' | 'color' | 'onDragStart' | 'onChange'> {
  value: number;
  dragRange?: number;
  setIsDrag: React.Dispatch<React.SetStateAction<boolean>>;
  onDragStart?: () => void;
  color?: string;
  ringColor?: string;
  shiftSensitivity?: number; // Shift 눌렀을 때 감도

  onChange?: (event: Event, value: number, activeThumb: number) => void;
  onChangeCommitted?: (event: React.SyntheticEvent | Event, value: number) => void;
}

export type InKnobProps = Omit<KnobProps, 'setIsDrag' | 'value'>;

function sliderToBox({
  /* eslint-disable @typescript-eslint/no-unused-vars */
  defaultValue,
  onMouseDown,
  onChange,
  onDragStart,
  onChangeCommitted,
  scale,
  /* eslint-enable @typescript-eslint/no-unused-vars */
  ...props
}: InKnobProps): Omit<BoxProps, 'sx'> {
  return { ...props };
}

const Knob = forwardRef<HTMLDivElement, KnobProps>(
  (
    {
      value,
      onChange,
      onDragStart,
      onChangeCommitted,
      dragRange = 150,
      setIsDrag: setIsDragParent,
      color = 'primary',
      ringColor = 'secondary',
      shiftSensitivity = 0.1,
      ...props
    },
    ref
  ) => {
    const handleValue = useMotionValue(value * (1 - dragRange));
    const progressScaleValue = useTransform(handleValue, [0, -dragRange], [0, 1]);

    const { isDrag, onMouseDown } = useDrag({
      handleValue,
      progressScaleValue,
      dragRange,
      shiftSensitivity,
      onDragStart,
      onChangeCommitted,
      setIsDragParent,
    });

    useMotionValueEvent(progressScaleValue, 'change', (latest) => {
      if (isDrag) onChange?.(new Event('change'), latest, 0);
    });

    useEffect(() => {
      if (!isDrag) handleValue.set(value * (1 - dragRange));
    }, [value, dragRange, handleValue, isDrag]);

    const knobOuter = useMemo(() => <KnobOuter color={color} />, [color]);
    const knobRail = useMemo(() => <KnobRail color={color} ringColor={ringColor} />, [color, ringColor]);

    return (
      <Box
        ref={ref}
        {...sliderToBox(props)}
        style={{ position: 'relative', width: '100%' }}
        onMouseDown={onMouseDown}
      >
        <svg viewBox="20 20 160 165">
          {knobOuter}
          {knobRail}
          <KnobThumb value={value} />
        </svg>
      </Box>
    );
  }
);

Knob.displayName = 'Knob';

export default Knob;
