'use client';

import { PluginName, CompanyName, CompanyWebsite } from '@/define';

import * as Juce from 'juce-framework-frontend';

import Box from '@mui/material/Box';
import Stack from '@mui/material/Stack';
import Button from '@mui/material/Button';

import JuceToggleBypass from '@/ui/Control/ToggleButton/JuceToggleBypass';
import { uesControlStore } from '@/store/ControlStore';

import Menu from './Menu';

const visitWebsite = Juce.getNativeFunction('visitWebsite');

export default function App() {
  const { setBypass } = uesControlStore();

  return (
    <Box
      sx={{
        position: 'static',
        px: 1,
        py: 1.5,
      }}
    >
      <Stack
        direction="row"
        alignItems="center"
        justifyContent="space-between"
        sx={{
          minHeight: 'var(--Header-minHeight)'
        }}
      >
        <Stack
          direction="row"
          alignItems="center"
          justifyContent="start"
          spacing={2}
        >
          <JuceToggleBypass
            identifier="bypassToggle"
            onChange={(e, value) => setBypass(value)}
            ignoreBypass
            invertValue
          />
          <Button
            variant="text"
            sx={{
              color: 'var(--mui-palette-secondary-main)',
              fontWeight: 'var(--mui-fontWeight-xl)',
            }}
            disableRipple
          >
            {PluginName}
          </Button>
        </Stack>

        <Stack
          direction="row"
          alignItems="center"
          justifyContent="end"
          spacing={2}
        >
          <Button
            onClick={() => visitWebsite(CompanyWebsite)}
            sx={{
              color: 'var(--mui-palette-common-white)',
              fontSize: 'var(--mui-fontSize-xs)',
              fontWeight: 'var(--mui-fontWeight-xl)',
            }}
            disableRipple
          >
            {CompanyName}
          </Button>
          <Menu />
        </Stack>
      </Stack>
    </Box>
  );
}
