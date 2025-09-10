'use client';

import { useState, useEffect, useRef } from 'react';
import * as Juce from 'juce-framework-frontend';

import Box, { type BoxProps } from '@mui/material/Box';
import Typography from '@mui/material/Typography';

import {
  controlParameterIndexAnnotation,
  toFixedDigits,
  LabelTypographySx
} from '@/define';

import Knob from './Knob';
import type { ValueToString } from '@/utils/valueToString';
import Tooltip from '@mui/material/Tooltip';
import { uesControlStore } from '@/store/ControlStore';

interface JuceSliderProps extends BoxProps {
  identifier: string,
  title?: string,
  subDigit?: number
  defaultValue?: number
  hideTitle?: boolean
  valueToString?: ValueToString
}

export default function JuceSlider({
  identifier,
  title,
  defaultValue = 0,
  subDigit = toFixedDigits,
  hideTitle = false,
  sx,
  valueToString,
  ...props
}: JuceSliderProps) {
  const ref = useRef<HTMLSpanElement|null>(null);
  const { focusAnchor, setAnchor } = uesControlStore();
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
    setAnchor(ref.current, isDrag || isOver);
  },[isDrag, isOver, setAnchor]);

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
        ...sx
      }}
      {...props}
    >
      <Tooltip
        open={focusAnchor === ref.current}
        title={printValue()}
        enterDelay={10}
      >
        <Knob
          ref={ref}
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
      </Tooltip>
      {!hideTitle &&
        <Typography
          className="cursorDefault"
          textAlign="center"
          sx={{
            ...LabelTypographySx,
            mt: '-0.5em',
          }}
        >
          {title || properties.name}
        </Typography>
      }
    </Box>
  );
}
