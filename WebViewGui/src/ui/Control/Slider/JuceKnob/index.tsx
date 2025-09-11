'use client';

import { useState, useEffect, useRef } from 'react';
import * as Juce from 'juce-framework-frontend';

import Box, { type BoxProps } from '@mui/material/Box';
import Typography from '@mui/material/Typography';

import {
  controlParameterIndexAnnotation,
  toFixedDigits,
  LabelTypographySx,
  testOpacity
} from '@/define';

import Knob from './Knob';
import type { ValueToString } from '@/utils/valueToString';
import Tooltip from '@mui/material/Tooltip';
import { uesControlStore } from '@/store/ControlStore';
import Stack from '@mui/material/Stack';
import type { UIProps } from '@/types/UI';

interface JuceSliderProps extends UIProps, BoxProps {
  identifier: string,
  title?: string,
  subDigit?: number
  defaultValue?: number
  hideTitle?: boolean
  valueToString?: ValueToString
  color?: string
  ringColor?: string
  lowIcon?: React.ReactNode
  highIcon?: React.ReactNode
}

export default function JuceSlider({
  identifier,
  title,
  defaultValue = 0,
  subDigit = toFixedDigits,
  hideTitle = false,
  valueToString,
  color = 'primary',
  ringColor = 'primary',
  ignoreBypass = false,
  addTest=[],
  lowIcon,
  highIcon,
  sx,
  ...props
}: JuceSliderProps) {
  const ref = useRef<HTMLSpanElement | null>(null);
  const { focusAnchor, setAnchor, bypassed } = uesControlStore();
  const sliderState = Juce.getSliderState(identifier);
  const [isDrag, setDrag] = useState<boolean>(false);
  const [isOver, setOver] = useState<boolean>(false);
  const [value, setValue] = useState<number>(sliderState.getNormalisedValue());
  const [properties, setProperties] = useState(sliderState.properties);

  const handleChange = (event: Event, newValue: number | number[]) => {
    if (typeof newValue === 'number') {
      sliderState.setNormalisedValue(newValue);
      setValue(newValue);
    }
  };

  const resetValue = () => {
    sliderState.setNormalisedValue(defaultValue);
    setValue(defaultValue);
  };

  const doubleClick = () => {
    resetValue();
  };

  const mouseDown = (e: React.MouseEvent) => {
    if (e.metaKey) {
      resetValue();
    } else {
      sliderState.sliderDragStarted();
    }
  };

  const changeCommitted = (event: Event | React.SyntheticEvent<Element, Event>, newValue: number | number[]) => {
    sliderState.setNormalisedValue(newValue);
    sliderState.sliderDragEnded();
  };

  useEffect(() => {
    const valueListenerId = sliderState.valueChangedEvent.addListener(() => {
      setValue(sliderState.getNormalisedValue());
    });
    const propertiesListenerId = sliderState.propertiesChangedEvent.addListener(
      () => setProperties(sliderState.properties)
    );

    return function cleanup() {
      sliderState.valueChangedEvent.removeListener(valueListenerId);
      sliderState.propertiesChangedEvent.removeListener(propertiesListenerId);
    };
  });

  useEffect(() => {
    setAnchor(ref.current, isDrag);
  }, [isDrag, isOver, setAnchor]);

  function calculateValue() {
    return sliderState.getScaledValue();
  }

  const printValue = () => {
    if (valueToString) {
      return valueToString(sliderState.getScaledValue(), subDigit);
    }

    return `${sliderState.getScaledValue().toFixed(subDigit)} ${properties.label}`;
  };

  return (
    <Box
      {...{
        [controlParameterIndexAnnotation]:
          sliderState.properties.parameterIndex,
      }}
      sx={{
        width: 'var(--knob-width)',
        flexShrink: 0,
        opacity: testOpacity([
          bypassed && !ignoreBypass,
          ...addTest
        ]),
        ...sx
      }}
      {...props}
    >
      <Knob
        ref={ref}
        color={color}
        ringColor={ringColor}
        setIsDrag={setDrag}
        value={value}
        scale={calculateValue}
        onChange={handleChange}
        min={0}
        max={1}
        step={1 / (properties.numSteps - 1)}
        onChangeCommitted={changeCommitted}
        onMouseDown={mouseDown}
        onDoubleClick={doubleClick}
        onMouseOver={() => setOver(true)}
        onMouseLeave={() => setOver(false)}
      />
      {!hideTitle &&
        <Stack
          direction="row"
          alignItems="center"
          justifyContent="center"
          spacing={1}
          sx={{
            mt: '-0.5em',
          }}
        >
          {lowIcon}
          <Tooltip
            open={
              (focusAnchor === ref.current)
              || (!focusAnchor) && isOver
            }
            title={printValue()}
            enterDelay={10}
            slotProps={{
              tooltip: {
                sx: {
                  mt: '0.5em !important',
                }
              }
            }}
          >
            <Typography
              textAlign="center"
              sx={{
                lineHeight: '1.0em',
                ...LabelTypographySx,
              }}
            >
              {title || properties.name}
            </Typography>
          </Tooltip>
          {highIcon}
        </Stack>
      }
    </Box>
  );
}
