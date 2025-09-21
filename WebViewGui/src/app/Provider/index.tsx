import AboutProvider from './AboutProvider';
import ActivateProvider from './ActivateProvider';
import AnalysisDataProvider from './AnalysisDataProvider';
import ControlParameterProvider from './ControlParameterProvider';
import IsDebug from './IsDebug';
import MantineProvider from './MantineProvider';
import PluginProvider from './PluginProvider';
import Snackbar from './Snackbar';

type ProviderProps = {
  children: React.ReactNode;
};

export default function Provider({ children }: ProviderProps) {
  return (
    <MantineProvider>
      {children}
      <IsDebug />
      <ActivateProvider />
      <PluginProvider />
      <AboutProvider />
      <AnalysisDataProvider />
      <Snackbar />
      <ControlParameterProvider />
    </MantineProvider>
  );
}
