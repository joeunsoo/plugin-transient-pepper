'use client';

import { useEffect, useMemo } from 'react';
import { useMotionValue, useTransform, useMotionValueEvent } from 'framer-motion';
import { type SliderProps } from '@mui/material/Slider';

import KnobRail from './KnobRail';
import KnobThumb from './KnobThumb';
import KnobOuter from './KnobOuter';
import { useDrag } from './useDrag';
import { Box, type BoxProps } from '@mantine/core';

export interface KnobProps extends Omit<SliderProps, 'value' | 'color' | 'onDragStart'> {
  value: number;
  dragRange?: number;
  setIsDrag: React.Dispatch<React.SetStateAction<boolean>>;
  onDragStart?: () => void;
  color?: string;
  ringColor?: string;
  shiftSensitivity?: number; // Shift 눌렀을 때 감도
}

export type InKnobProps = Omit<KnobProps, 'setIsDrag'| 'value'>;

// eslint-disable-next-line @typescript-eslint/no-unused-vars
function sliderToBox({ defaultValue, onMouseDown, onChange, onDragStart, onChangeCommitted, scale, ...props }: InKnobProps): Omit<BoxProps, 'sx'> {
  return { ...props };
}

export default function JuceSlider({
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
}: KnobProps) {
  // const [isDrag, setIsDrag] = useState(false);
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
