'use client';

import { useState, useEffect } from 'react';
import * as Juce from 'juce-framework-frontend';

import Box, { type BoxProps } from '@mui/material/Box';
import Typography from '@mui/material/Typography';

import controlParameterIndexAnnotation from '@/src/define/controlParameterIndexAnnotation';
import { toFixedDigits } from '@/src/define';
import { LabelTypographySx } from '@/ui/Style';

import Knob from './Knob';

interface JuceSliderProps extends BoxProps {
  identifier: string,
  title?: string,
  subDigit?: number
  defaultValue?: number
  hideTitle?: boolean
}

export default function JuceSlider({
  identifier,
  title,
  defaultValue = 0,
  subDigit = toFixedDigits,
  hideTitle = false,
  sx,
  ...props
}: JuceSliderProps) {
  const sliderState = Juce.getSliderState(identifier);

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

  function calculateValue() {
    return sliderState.getScaledValue();
  }

  return (
    <Box
      {...{
        [controlParameterIndexAnnotation]:
          sliderState.properties.parameterIndex,
      }}
      sx={{
        width: '6.5em',
        ...sx
      }}
      {...props}
    >
      <Knob
        value={value}
        scale={calculateValue}
        onChange={handleChange}
        min={0}
        max={1}
        step={1 / (properties.numSteps - 1)}
        onChangeCommitted={changeCommitted}
        onMouseDown={mouseDown}
        onDoubleClick={doubleClick}
      />
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
      <Typography
        className="cursorDefault"
        textAlign="center"
        sx={{
          ...LabelTypographySx,
        }}
      >
        {sliderState.getScaledValue().toFixed(subDigit)} {properties.label}
      </Typography>
    </Box>
  );
}
