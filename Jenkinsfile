pipeline {
  agent any
  stages {
    stage('Build') {
      agent any
      steps {
        dir('C++') {
          sh 'make'
          archiveArtifacts artifacts: 'bin/*' , fingerprint: true
        }
      }
    }
  }
  post {


      // Clean after build
      always {

        success {
                    setBuildStatus("Build succeeded", "SUCCESS");
                }
                failure {
                    setBuildStatus("Build failed", "FAILURE");
                }

          cleanWs(cleanWhenNotBuilt: false,
                  deleteDirs: true,
                  disableDeferredWipeout: true,
                  notFailBuild: true,
                  patterns: [[pattern: '.gitignore', type: 'INCLUDE'],
                             [pattern: '.propsfile', type: 'EXCLUDE']])
      }
  }
}