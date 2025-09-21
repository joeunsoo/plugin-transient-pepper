'use client';

import { useState, useEffect, useRef, useCallback } from 'react';
import * as Juce from 'juce-framework-frontend';

import {
  controlParameterIndexAnnotation,
  toFixedDigits,
  LabelTypographySx,
  testOpacity,
  mantineSpace,
} from '@/define';

import Knob from './Knob';
import type { ValueToString } from '@/utils/valueToString';
import { useControlStore } from '@/store/ControlStore';
import type { UIProps } from '@/types/UI';
import { Box, Group, rem, Text, Tooltip, type BoxProps } from '@mantine/core';

interface JuceSliderProps extends UIProps, Omit<BoxProps,'onChange'> {
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
  onChange?: (v: number) => void
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
  addTest = [],
  lowIcon,
  highIcon,
  style,
  onChange,
  ...props
}: JuceSliderProps) {
  const ref = useRef<HTMLDivElement | null>(null);
  const { focusAnchor, setAnchor, bypassed } = useControlStore();
  const sliderState = Juce.getSliderState(identifier);
  const [isDrag, setDrag] = useState<boolean>(false);
  const [isOver, setOver] = useState<boolean>(false);
  const [value, setValue] = useState<number>(sliderState.getNormalisedValue());
  const [properties, setProperties] = useState(sliderState.properties);

  const handleChange = (event: Event, newValue: number | number[]) => {
    if (typeof newValue === 'number') {
      sliderState.setNormalisedValue(newValue);
      setValue(newValue);
      if (onChange) {
        onChange(newValue);
      }
    }
  };

  const resetValue = () => {
    sliderState.setNormalisedValue(defaultValue);
    setValue(defaultValue);
    if (onChange) {
      onChange(defaultValue);
    }
  };

  const doubleClick = () => {
    resetValue();
  };

  const dragStart = () => {
    sliderState.sliderDragStarted();
  };

  const mouseDown = (e: React.MouseEvent) => {
    if (e.metaKey) {
      resetValue();
    } else {
      // sliderState.sliderDragStarted();
    }
  };

  const changeCommitted = useCallback((event: Event | React.SyntheticEvent<Element, Event>, newValue: number | number[]) => {
    sliderState.setNormalisedValue(newValue);
    sliderState.sliderDragEnded();
  }, [sliderState]);

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
  }, [sliderState]);

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
      style={{
        width: 'var(--knob-width)',
        flexShrink: 0,
        opacity: testOpacity([
          bypassed && !ignoreBypass,
          ...addTest
        ]),
        ...style
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
        onDragStart={dragStart}
        onMouseOver={() => setOver(true)}
        onMouseLeave={() => setOver(false)}
      />
      {!hideTitle &&
        <Group
          align="center"
          justify="center"
          gap={rem(mantineSpace * 1)}
          style={{
            transform: 'translateY(-0.5em)'
          }}
        >
          {lowIcon}
          <Tooltip
            opened={
              (focusAnchor === ref.current)
              || (!focusAnchor) && isOver
            }
            label={printValue()}
            position="bottom"
            openDelay={10}
            bg="secondary.9"
            c="white"
            px="0.4rem"
            py="0.2rem"
            style={{
              fontSize: '0.7em',
            }}
          >
            <Text
              ta="center"
              sx={{
                ...LabelTypographySx,
                lineHeight: '1.5em',
              }}
            >
              {title || properties.name}
            </Text>
          </Tooltip>
          {highIcon}
        </Group>
      }
    </Box>
  );
}
