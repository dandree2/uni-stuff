
import org.lwjgl.glfw.*;
import org.lwjgl.opengl.*;

import static org.lwjgl.glfw.Callbacks.*;
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.*;

public class HelloWorld {
	
	private long               window;
	private final static short WIDTH = 1024;
	private final static short HEIGHT = 1024;
	
	protected GLFWKeyCallback  keyCallback;
	
	public void run(){
		try {
			InitGL();
			CreateWindow();
			Run();
			
			// Free the window callbacks and destroy the window
			glfwFreeCallbacks(window);
			glfwDestroyWindow(window);
		} finally {
			// Terminate GLFW and free the error callback
			glfwTerminate();
			glfwSetErrorCallback(null).free();
		}
	}
	
	private void InitGL() {
		// Setup an error callback. The default implementation
		// will print the error message in System.err.
		GLFWErrorCallback.createPrint(System.err).set();

		// Initialize GLFW. Most GLFW functions will not work before doing this.
		if ( !glfwInit() )
			throw new IllegalStateException("Unable to initialize GLFW");

		// Configure our window
		glfwDefaultWindowHints(); // optional, the current window hints are already the default
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // the window will stay hidden after creation
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); // the window will be resizable
	}
	
	private void CreateWindow() {
		// Create the window.
		window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World!", NULL, NULL);
		if ( window == NULL )
			throw new RuntimeException("Failed to create the GLFW window");
		
		// Construct and bind the keyboard handler.
		glfwSetKeyCallback(window, keyCallback = new KeyboardHandler());

		// Get the resolution of the primary monitor.
		GLFWVidMode vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		
		// Center our window.
		glfwSetWindowPos(
			window,
			(vidmode.width() - WIDTH) / 2,
			(vidmode.height() - HEIGHT) / 2
		);

		// Make the OpenGL context current.
		glfwMakeContextCurrent(window);
		
		// Enable v-sync.
		glfwSwapInterval(1);

		// Make the window visible.
		glfwShowWindow(window);
	}
	
	public void update() {
		if (KeyboardHandler.isKeyDown(GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, true); // We will detect this in our rendering loop
		}
    }
	
	private void Run() {
		GL.createCapabilities();

		// Run the rendering loop until the user has attempted to close
		// the window or has pressed the ESCAPE key.
		while ( !glfwWindowShouldClose(window) ) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			glLoadIdentity();

			glTranslatef(0f,0.0f,0.0f);
			glRotatef(30.0f,1.0f,1.0f,0.0f);
			glColor3f(0.5f,0.5f,1.0f);
			
			glBegin(GL_QUADS);
			
				GL11.glColor3f(0.5f,0.5f,0.0f);
				GL11.glVertex3f(0.5f,0.5f,-0.5f);
				GL11.glVertex3f(-0.5f,0.5f,-0.5f);
				GL11.glVertex3f(-0.5f,0.5f,0.5f);
				GL11.glVertex3f(0.5f,0.5f,0.5f);
				
				GL11.glColor3f(0.5f,0.5f,0.0f);
				GL11.glVertex3f(0.5f,-0.5f,0.5f);
				GL11.glVertex3f(-0.5f,-0.5f,0.5f);
				GL11.glVertex3f(-0.5f,-0.5f,-0.5f);
				GL11.glVertex3f(0.5f,-0.5f,-0.5f);
				
				GL11.glColor3f(0.5f,0.0f,0.0f);
				GL11.glVertex3f(0.5f,0.5f,0.5f);
				GL11.glVertex3f(-0.5f,0.5f,0.5f);
				GL11.glVertex3f(-0.5f,-0.5f,0.5f);
				GL11.glVertex3f(0.5f,-0.5f,0.5f);
				
				GL11.glColor3f(0.5f,0.5f,0.0f);
				GL11.glVertex3f(0.5f,-0.5f,-0.5f);
				GL11.glVertex3f(-0.5f,-0.5f,-0.5f);
				GL11.glVertex3f(-0.5f,0.5f,-0.5f);
				GL11.glVertex3f(0.5f,0.5f,-0.5f);
				
				GL11.glColor3f(0.0f,0.0f,0.5f);
				GL11.glVertex3f(-0.5f,0.5f,0.5f);
				GL11.glVertex3f(-0.5f,0.5f,-0.5f);
				GL11.glVertex3f(-0.5f,-0.5f,-0.5f);
				GL11.glVertex3f(-0.5f,-0.5f,0.5f);
				
				GL11.glColor3f(0.5f,0.0f,0.5f);
				GL11.glVertex3f(0.5f,0.5f,-0.5f);
				GL11.glVertex3f(0.5f,0.5f,0.5f);
				GL11.glVertex3f(0.5f,-0.5f,0.5f);
				GL11.glVertex3f(0.5f,-0.5f,-0.5f);
			
			glEnd();
			
			glfwSwapBuffers(window); // swap the color buffers

			// Poll for window events. The key callback above will only be
			// invoked during this call.
			glfwPollEvents();
			
			update();
		}
	}

	public static void main(String[] args) {
		new HelloWorld().run();
	}

}