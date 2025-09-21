import MantineProvider from './MantineProvider';
import AboutProvider from './AboutProvider';
import AnalysisDataProvider from './AnalysisDataProvider';
import ControlParameterProvider from './ControlParameterProvider';
import ActivateProvider from './ActivateProvider';
import IsDebug from './IsDebug';
import Snackbar from './Snackbar';

type ProviderProps = {
  children: React.ReactNode
}

export default function Provider({
  children
}: ProviderProps) {
  return (
      <MantineProvider>
        {children}
        <IsDebug />
        <ActivateProvider />
        <AboutProvider />
        <AnalysisDataProvider />
        <Snackbar />
        <ControlParameterProvider />
      </MantineProvider>
  );
}
