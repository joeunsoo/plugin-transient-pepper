'use client';

import { useState, useEffect } from 'react';
import { motion, useMotionValue, useTransform, useMotionValueEvent } from 'framer-motion';
import Box, { type BoxProps } from '@mui/material/Box';
import Slider, { type SliderProps } from '@mui/material/Slider';

import KnobRail from './KnobRail';
import KnobThumb from './KnobThumb';
import KnobOuter from './KnobOuter';

export interface KnobProps extends Omit<SliderProps, 'value' | 'color' | 'onDragStart'> {
  value: number;
  dragRange?: number;
  setIsDrag: React.Dispatch<React.SetStateAction<boolean>>;
  onDragStart?: () => void;
  color?: string;
  ringColor?: string;
  shiftSensitivity?: number; // Shift 눌렀을 때 감도
}

export type InKnobProps = Omit<KnobProps, 'setIsDrag'>;

// eslint-disable-next-line @typescript-eslint/no-unused-vars
function sliderToBox({ defaultValue, onMouseDown, onChange, onDragStart, onChangeCommitted, scale, ...props }: InKnobProps): BoxProps {
  return { ...props };
}

export default function JuceSlider({
  dragRange = 150,
  setIsDrag: setIsDragParent,
  color = 'primary',
  ringColor = 'secondary',
  shiftSensitivity = 0.1,
  ...props
}: KnobProps) {
  const [isDrag, setIsDrag] = useState(false);
  const handleValue = useMotionValue(props.value * (1 - dragRange));
  const progressScaleValue = useTransform(handleValue, [0, -dragRange], [0, 1]);

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
    <Box {...sliderToBox(props)}>
      <Box
        sx={{ position: 'relative', width: '100%' }}
        onMouseDown={(e: React.MouseEvent) => {
          if (e.button !== 0) return;

          setIsDrag(true);
          setIsDragParent(true);
          if (props.onDragStart) props.onDragStart();

          let lastY = e.clientY;

          function onMouseMove(ev: MouseEvent) {
            const dy = ev.clientY - lastY;
            const sensitivity = ev.shiftKey ? shiftSensitivity : 1;

            let newValue = handleValue.get() + dy * sensitivity;

            // dragConstraints 적용
            if (newValue < -dragRange) newValue = -dragRange;
            if (newValue > 0) newValue = 0;

            handleValue.set(newValue);
            lastY = ev.clientY; // 이전 기준 갱신
          }

          function onMouseUp() {
            if (props.onChangeCommitted) {
              props.onChangeCommitted(new Event('change'), progressScaleValue.get());
            }
            setIsDrag(false);
            setIsDragParent(false);

            window.removeEventListener('mousemove', onMouseMove);
            window.removeEventListener('mouseup', onMouseUp);
          }

          window.addEventListener('mousemove', onMouseMove);
          window.addEventListener('mouseup', onMouseUp);
        }}
      >
        <motion.div
          className="handle"
          // drag="none"
          style={{ y: handleValue, display: 'none' }}
        />

        <svg viewBox="20 20 160 165">
          <KnobOuter color={color} />
          <KnobRail color={color} ringColor={ringColor} />
          <KnobThumb value={props.value} />
        </svg>
      </Box>

      <Slider {...props} value={props.value} sx={{ display: 'none' }} />
    </Box>
  );
}
