'use client';

import { useState, useEffect } from 'react';
import * as Juce from 'juce-framework-frontend';

import Stack, { type StackProps } from '@mui/material/Stack';

import type { SelectChangeEvent } from '@mui/material/Select';

import { controlParameterIndexAnnotation, LabelTypographySx, testOpacity } from '@/define';
import Typography from '@mui/material/Typography';

import Select from './Select';
import { uesControlStore } from '@/store/ControlStore';
import type { UIProps } from '@/types/UI';

interface JuceComboBoxProps extends UIProps, StackProps {
  identifier: string,
  hideTitle?: boolean
}

export default function JuceComboBox({
  identifier,
  hideTitle = false,
  ignoreBypass,
  addTest = [],
  sx,
  ...props
}: JuceComboBoxProps) {
  const comboBoxState = Juce.getComboBoxState(identifier);
    const { bypassed } = uesControlStore();

  const [value, setValue] = useState(comboBoxState.getChoiceIndex());
  const [properties, setProperties] = useState(comboBoxState.properties);

  const handleChange = (event: SelectChangeEvent, nextValue: string | number) => {
    if (nextValue !== null) {
      comboBoxState.setChoiceIndex(nextValue);
      setValue(nextValue);
    }
  };

  useEffect(() => {
    const valueListenerId = comboBoxState.valueChangedEvent.addListener(() => {
      setValue(comboBoxState.getChoiceIndex());
    });
    const propertiesListenerId =
      comboBoxState.propertiesChangedEvent.addListener(() => {
        setProperties(comboBoxState.properties);
      });

    return function cleanup() {
      comboBoxState.valueChangedEvent.removeListener(valueListenerId);
      comboBoxState.propertiesChangedEvent.removeListener(propertiesListenerId);
    };
  }, [comboBoxState]);

  return (
    <Stack
      justifyContent="space-between"
      {...{
        [controlParameterIndexAnnotation]:
          comboBoxState.properties.parameterIndex,
      }}
      sx={{
        opacity: testOpacity([
          bypassed && !ignoreBypass,
          ...addTest
        ]),
        flexGrow:1,
        ...sx
      }}
      {...props}
    >
      <Select
        value={value}
        choices={properties.choices}
        onChange={handleChange}
      />
      {!hideTitle &&
        <Typography
          textAlign="center"
          sx={{
            ...LabelTypographySx,
            lineHeight: '1.5em',
            flexShrink:0,
          }}
        >
          {properties.name}
        </Typography>
      }
    </Stack>
  );
}
