'use client';

import { useState, useEffect } from 'react';
import * as Juce from 'juce-framework-frontend';

import Box, { type BoxProps } from '@mui/material/Box';

import { controlParameterIndexAnnotation } from '@/define';

import Button from './Button';

interface JuceCheckboxProps
  extends Omit<BoxProps, 'title'> {
  identifier: string,
  title?: React.ReactNode,
  invertValue?: boolean
}

export default function JuceCheckbox({
  identifier,
  title,
  invertValue = false,
  sx,
  ...props
}: JuceCheckboxProps) {
  const checkboxState = Juce.getToggleState(identifier);

  const [value, setValue] = useState(checkboxState.getValue());
  const [properties, setProperties] = useState(checkboxState.properties);

  const handleChange = (value: boolean) => {
    checkboxState.setValue(invertValue ? !value : value);
    setValue(value);
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
