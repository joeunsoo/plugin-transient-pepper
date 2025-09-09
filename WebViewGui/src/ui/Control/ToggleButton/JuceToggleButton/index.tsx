'use client';

import { useState, useEffect } from 'react';
import * as Juce from 'juce-framework-frontend';

import Box from '@mui/material/Box';

import { controlParameterIndexAnnotation } from '@/src/define';

import Button from './Button';

type JuceCheckboxProps = {
  identifier: string,
  title?: string,
  invertValue?: boolean
}

export default function JuceCheckbox({
  identifier,
  title,
  invertValue=false
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
    >
      <Button
        value={invertValue ? !value : value}
        handleChange={handleChange}
        label={title || properties.name}
      />
    </Box>
  );
}
