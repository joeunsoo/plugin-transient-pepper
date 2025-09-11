'use client';

import { useState, useEffect } from 'react';
import * as Juce from 'juce-framework-frontend';

import Box, { type BoxProps } from '@mui/material/Box';

import { testOpacity, controlParameterIndexAnnotation } from '@/define';

import Button from './Button';
import { uesControlStore } from '@/store/ControlStore';
import type { UIProps } from '@/types/UI';

interface JuceCheckboxProps
  extends UIProps, Omit<BoxProps, 'title' | 'onChange'> {
  identifier: string,
  invertValue?: boolean
  onChange?: (e: Event, value: boolean) => void
}

export default function JuceCheckbox({
  identifier,
  invertValue = false,
  sx,
  onChange,
  ignoreBypass = false,
  addTest=[],
  ...props
}: JuceCheckboxProps) {
  const { bypassed } = uesControlStore();
  const checkboxState = Juce.getToggleState(identifier);

  const [value, setValue] = useState(checkboxState.getValue());

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
    });

    return function cleanup() {
      checkboxState.valueChangedEvent.removeListener(valueListenerId);
    };
  });

  return (
    <Box
      {...{
        [controlParameterIndexAnnotation]:
          checkboxState.properties.parameterIndex,
      }}
      sx={{
        opacity: testOpacity([
          bypassed && !ignoreBypass,
          ...addTest
        ]),
        ...sx
      }}
      {...props}
    >
      <Button
        value={invertValue ? !value : value}
        handleChange={handleChange}
      />
    </Box>
  );
}
