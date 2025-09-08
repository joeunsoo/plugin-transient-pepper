'use client';

import { useState, useEffect } from 'react';
import * as Juce from 'juce-framework-frontend';

import Box from '@mui/material/Box';
import Checkbox from '@mui/material/Checkbox';
import FormGroup from '@mui/material/FormGroup';
import FormControlLabel from '@mui/material/FormControlLabel';

import controlParameterIndexAnnotation from '@/src/define/controlParameterIndexAnnotation';

type JuceCheckboxProps = {
  identifier: string,
}

export default function JuceCheckbox({
  identifier
}: JuceCheckboxProps) {
  const checkboxState = Juce.getToggleState(identifier);

  const [value, setValue] = useState(checkboxState.getValue());
  const [properties, setProperties] = useState(checkboxState.properties);

  const handleChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    checkboxState.setValue(event.target.checked);
    setValue(event.target.checked);
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

  const cb = <Checkbox checked={value} onChange={handleChange} />;

  return (
    <Box
      {...{
        [controlParameterIndexAnnotation]:
          checkboxState.properties.parameterIndex,
      }}
    >
      <FormGroup>
        <FormControlLabel control={cb} label={properties.name} />
      </FormGroup>
    </Box>
  );
}
