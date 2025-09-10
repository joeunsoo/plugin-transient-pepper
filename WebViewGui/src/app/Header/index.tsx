'use client';

import { PluginName, CompanyName, CompanyWebsite } from '@/define';

import * as Juce from 'juce-framework-frontend';

import Box from '@mui/material/Box';
import Stack from '@mui/material/Stack';
import Button from '@mui/material/Button';

import { useAboutStore } from '@/store/AboutStore';

import Menu from './Menu';

const visitWebsite = Juce.getNativeFunction('visitWebsite');

export default function App() {
  const { setOpen } = useAboutStore();

  return (
    <Box
      sx={{
        position: 'static',
        px: 1,
        py: 1.5,
        backgroundColor: 'var(--mui-palette-primary-darkest)',
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
        <Button
          onClick={() => setOpen(true)}
          variant="text"
          sx={{
            color: 'var(--mui-palette-common-white)',
            fontWeight: 'var(--mui-fontWeight-xl)',
          }}
          disableRipple
        >
          {PluginName}
        </Button>

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
