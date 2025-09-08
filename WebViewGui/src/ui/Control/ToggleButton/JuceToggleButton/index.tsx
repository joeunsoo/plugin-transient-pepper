'use client';

import { useState, useEffect } from 'react';
import * as Juce from 'juce-framework-frontend';

import Box from '@mui/material/Box';

import controlParameterIndexAnnotation from '@/src/define/controlParameterIndexAnnotation';

import Button from './Button';

type JuceCheckboxProps = {
  identifier: string,
}

export default function JuceCheckbox({
  identifier
}: JuceCheckboxProps) {
  const checkboxState = Juce.getToggleState(identifier);

  const [value, setValue] = useState(checkboxState.getValue());
  const [properties, setProperties] = useState(checkboxState.properties);

  const handleChange = (value: boolean) => {
    checkboxState.setValue(value);
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
    >
      <Button
        value={value}
        handleChange={handleChange}
        label={properties.name}
      />
    </Box>
  );
}
