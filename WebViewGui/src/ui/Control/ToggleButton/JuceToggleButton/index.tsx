'use client';

import { useState, useEffect } from 'react';
import * as Juce from 'juce-framework-frontend';

import Box, { type BoxProps } from '@mui/material/Box';

import { controlParameterIndexAnnotation, ignoreBypassOpacity } from '@/define';

import Button from './Button';
import { uesControlStore } from '@/store/ControlStore';

interface JuceCheckboxProps
  extends Omit<BoxProps, 'title' | 'onChange'> {
  identifier: string,
  title?: React.ReactNode,
  invertValue?: boolean
  onChange?: (e: Event, value: boolean) => void
  ignoreBypass?:boolean
}

export default function JuceCheckbox({
  identifier,
  title,
  invertValue = false,
  sx,
  onChange,
  ignoreBypass=false,
  ...props
}: JuceCheckboxProps) {
  const { bypassed } = uesControlStore();
  const checkboxState = Juce.getToggleState(identifier);

  const [value, setValue] = useState(checkboxState.getValue());
  const [properties, setProperties] = useState(checkboxState.properties);

  const handleChange = (value: boolean) => {
    checkboxState.setValue(invertValue ? !value : value);
    setValue(value);
    if (onChange) {
      onChange(new Event('change'), value);
    }
  };

  useEffect(() => {
    const valueListenerId = checkboxState.valueChangedEvent.addListener(() => {
      setValue(checkboxState.getValue());
    });
    const propertiesListenerId =
      checkboxState.propertiesChangedEvent.addListener(() => setProperties(checkboxState.properties));

    return function cleanup() {
      checkboxState.valueChangedEvent.removeListener(valueListenerId);
      checkboxState.propertiesChangedEvent.removeListener(propertiesListenerId);
    };
  });

  return (
    <Box
      {...{
        [controlParameterIndexAnnotation]:
          checkboxState.properties.parameterIndex,
      }}
      sx={{
        width: 'var(--knob-width)',
        opacity: (!ignoreBypass && bypassed) ? ignoreBypassOpacity : 1.0,
        ...sx
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
