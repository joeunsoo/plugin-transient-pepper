'use client';

import { useState, useEffect } from 'react';
import * as Juce from 'juce-framework-frontend';

import { Box, type BoxProps } from '@mantine/core';

import { testOpacity, controlParameterIndexAnnotation } from '@/define';

import Button from './Button';
import { useControlStore } from '@/store/ControlStore';
import type { UIProps } from '@/types/UI';

interface JuceCheckboxProps
  extends UIProps, Omit<BoxProps, 'title' | 'onChange'> {
  identifier: string,
  title?: React.ReactNode,
  invertValue?: boolean
  onChange?: (e: Event, value: boolean) => void
}

export default function JuceCheckbox({
  identifier,
  title,
  invertValue = false,
  style,
  onChange,
  ignoreBypass = false,
  addTest=[],
  ...props
}: JuceCheckboxProps) {
  const { bypassed } = useControlStore();
  const checkboxState = Juce.getToggleState(identifier);

  const [value, setValue] = useState(checkboxState.getValue());
  const [properties, setProperties] = useState(checkboxState.properties);

  const handleChange = (value: boolean) => {
    const newValue = invertValue ? !value : value;
    checkboxState.setValue(newValue);
    setValue(newValue);
    if (onChange) {
      onChange(new Event('change'), newValue);
    }
  };

  useEffect(() => {
    const valueListenerId = checkboxState.valueChangedEvent.addListener(() => {
      setValue(checkboxState.getValue());
      if (onChange) {
        onChange(new Event('change'), checkboxState.getValue());
      }
    });
    const propertiesListenerId =
      checkboxState.propertiesChangedEvent.addListener(() => setProperties(checkboxState.properties));

    return function cleanup() {
      checkboxState.valueChangedEvent.removeListener(valueListenerId);
      checkboxState.propertiesChangedEvent.removeListener(propertiesListenerId);
    };
  });

  useEffect(() => {
    setValue(checkboxState.getValue());
    if (onChange) {
      onChange(new Event('change'), checkboxState.getValue());
    }
  // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  return (
    <Box
      {...{
        [controlParameterIndexAnnotation]:
          checkboxState.properties.parameterIndex,
      }}
      style={{
        width: 'var(--knob-width)',
        opacity: testOpacity([
          bypassed && !ignoreBypass,
          ...addTest
        ]),
        ...style
      }}
      {...props}
    >
      <Button
        value={invertValue ? !value : value}
        handleChange={handleChange}
        label={title || properties.name}
      />
    </Box>
  );
}
